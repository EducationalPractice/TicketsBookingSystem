#include "DataHandler.h"
#include <fstream>

DataHandler::DataHandler()
{
}


DataHandler::~DataHandler()
{
}


void DataHandler::findSuitedTrains(vector<TrainInformation>& trains)
{
	string num = CustomerOrder::getTrainNumber();
	string where = CustomerOrder::getWhere();
	string from = CustomerOrder::getFrom();
	string date = CustomerOrder::getDate();

	TrainInformation train;

	if (num != "")
	{
		bool isOk = loadTrain(num, date, train);
		if (isOk)
			trains.push_back(train);
	}
	else
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile("trains.xml");
		tinyxml2::XMLElement* pTrain = doc.FirstChild()
		                                  ->FirstChildElement("Train");

		while (pTrain != nullptr)
		{
			bool isOk = loadTrain(pTrain, num, date, train);
			if (isOk)
				trains.push_back(train);

			pTrain = pTrain->NextSiblingElement("Train");
		}
	}
	chain(trains);
}

bool DataHandler::isBlocked(const SeatOrderInformation& order,
                            const string& from,
                            const string& where,
                            const vector<StationInformation>* stations)
{
	int ai = 0, aj = 0, bi = 0, bj = 0;

	for (int i = 0; i < stations->size(); ++i)
	{
		if (from == (*stations)[i])
			ai = i;
		if (where == (*stations)[i])
			aj = i;
		if (order.getFrom() == (*stations)[i])
			bi = i;
		if (order.getWhere() == (*stations)[i])
			bj = i;
	}


	return !(aj <= bi || bj <= ai);
}

void DataHandler::setTrainName(tinyxml2::XMLElement* pTrain, TrainInformation& train)
{
	train.setFullName(pTrain->FirstChildElement("FullName")->GetText());
}

void DataHandler::setTrainNumber(tinyxml2::XMLElement* pTrain, TrainInformation& train)
{
	train.setTrainNumber(pTrain->Attribute("number"));
}

void DataHandler::readOrder(tinyxml2::XMLElement* pOrder,
                            vector<RailCarInformation>& RailCars)
{
	SeatOrderInformation order;
	string from, where;
	size_t railCarNum, seat;

	from = pOrder->Attribute("from");
	where = pOrder->Attribute("where");

	pOrder->QueryUnsignedAttribute("railCarNum", &railCarNum);
	pOrder->QueryUnsignedAttribute("seatNum", &seat);

	order.setFrom(from);
	order.setWhere(where);
	order.setSeatNum(seat);

	if (isBlocked(order,
	              CustomerOrder::getFrom(),
	              CustomerOrder::getWhere(),
	              RailCars[railCarNum - 1].getStations()))
	{
		RailCars[railCarNum - 1].addBookedSeat(seat);
	}
}

void DataHandler::readOrders(tinyxml2::XMLElement* pDate,
                             vector<RailCarInformation>& RailCars)
{
	tinyxml2::XMLElement* pOrder = pDate->FirstChildElement("Order");

	while (pOrder != nullptr)
	{
		readOrder(pOrder, RailCars);

		pOrder = pOrder->NextSiblingElement("Order");
	}
}

void DataHandler::loadRailCars(tinyxml2::XMLElement* pTrain, TrainInformation& train)
{
	vector<RailCarInformation> railCars;

	tinyxml2::XMLElement* pRailCars = pTrain->FirstChildElement("RailCars");
	tinyxml2::XMLElement* pRailCar = pRailCars->FirstChildElement("RailCar");

	while (pRailCar != nullptr)
	{
		int number;
		string type;

		pRailCar->QueryIntAttribute("number", &number);
		type = pRailCar->Attribute("type");

		if (type == "P")
			railCars.push_back(RailCarInformation(RailCarType::ReservedSeat, number));
		else if (type == "C")
			railCars.push_back(RailCarInformation(RailCarType::Compartment, number));
		else
			railCars.push_back(RailCarInformation(RailCarType::Luxe, number));

		pRailCar = pRailCar->NextSiblingElement("RailCar");
	}
	sort(railCars.begin(), railCars.end(), *compareBySeatNum);

	for (auto& el : railCars)
	{
		el.setStations(train.getStations());
	}

	readOrders(getDateLink(pTrain, CustomerOrder::getDate()), railCars);

	train.setRailCars(railCars);
}


bool DataHandler::loadTrain(const string& num,
                            const string& date,
                            TrainInformation& train)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("trains.xml");

	tinyxml2::XMLElement* pTrain = getTrain(doc, num);

	return loadTrain(pTrain, num, date, train);
}

bool DataHandler::loadTrain(tinyxml2::XMLElement* pTrain,
                            const string& num,
                            const string& date,
                            TrainInformation& train)
{
	vector<StationInformation> stations;
	vector<string> dates;


	getTrainStations(pTrain, stations);
	getTrainsDates(pTrain, dates);

	if (!(checkTrainByRoute(CustomerOrder::getFrom(),
		CustomerOrder::getWhere(), stations) &&
		checkTrainByTime(date, dates)))
	{
		return false;
	}
	else
	{
		setTrainName(pTrain, train);
		setTrainNumber(pTrain, train);

		train.setStations(stations);

		loadRailCars(pTrain, train);

		return true;
	}
}

StationInformation DataHandler::proccesStation(tinyxml2::XMLElement* pStation)
{
	StationInformation station;

	double dbl_buf;
	station.setName(pStation->Attribute("place"));
	station.setTimeOfArrival(pStation->Attribute("time"));

	pStation->QueryDoubleAttribute("distance", &dbl_buf);
	station.setDistance(dbl_buf);

	return station;
}

void DataHandler::getTrainStations(tinyxml2::XMLElement* pTrain,
                                   vector<StationInformation>& stations)
{
	tinyxml2::XMLElement* pStations = pTrain->FirstChildElement("Stations");
	tinyxml2::XMLElement* pStation = pStations->FirstChildElement("Station");

	while (pStation != nullptr)
	{
		stations.push_back(proccesStation(pStation));
		pStation = pStation->NextSiblingElement("Station");
	}
}

void DataHandler::getTrainsDates(tinyxml2::XMLElement* pTrain,
                                 vector<string>& dates)
{
	tinyxml2::XMLElement* pDate = pTrain->FirstChildElement("Orders");

	while (pDate != nullptr)
	{
		string date;
		date = pDate->Attribute("date");
		dates.push_back(date);

		pDate = pDate->NextSiblingElement("Orders");
	}
}

bool DataHandler::checkTrainByRoute(const string& from,
                                    const string& where,
                                    const vector<StationInformation>& stations)
{
	int i = 0, j = 0, counter = 1;
	for (const auto& el : stations)
	{
		if (from == el)
			i = counter;
		if (where == el)
			j = counter;
		counter++;
	}
	return j > i && i != 0 && j != 0;
}


bool DataHandler::checkTrainByTime(string date, const vector<string>& dates)
{
	for (const auto& el : dates)
	{
		if (el == date)
			return true;
	}
	return false;
}

void DataHandler::chain(vector<TrainInformation>& trains)
{
	for (int i = 0; i < trains.size(); ++i)
	{
		trains[i].chainRailCars();
	}
}

tinyxml2::XMLElement* DataHandler::getTrain(tinyxml2::XMLDocument& doc,
                                            const string& num)
{
	tinyxml2::XMLElement* pTrain = doc.FirstChild()->FirstChildElement("Train");

	while (pTrain != nullptr)
	{
		if (pTrain->Attribute("number") == num)
			return pTrain;
		pTrain = pTrain->NextSiblingElement("Train");
	}
	return nullptr;
}

tinyxml2::XMLElement* DataHandler::formCustomerOrder(tinyxml2::XMLDocument& doc,
                                                     size_t place)
{
	string from = CustomerOrder::getFrom();
	string where = CustomerOrder::getWhere();

	size_t railCarNum = CustomerOrder::getRailCarNumber();

	tinyxml2::XMLElement* pOrder = doc.NewElement("Order");

	pOrder->SetAttribute("from", from.c_str());
	pOrder->SetAttribute("where", where.c_str());
	pOrder->SetAttribute("railCarNum", railCarNum);
	pOrder->SetAttribute("seatNum", place);

	return pOrder;
}

tinyxml2::XMLElement* DataHandler::getDateLink(tinyxml2::XMLElement* pTrain,
                                               const string& date)
{
	tinyxml2::XMLElement* xmlDate = pTrain
		->FirstChildElement("Orders");

	while (xmlDate != nullptr)
	{
		if (xmlDate->Attribute("date") == date)
		{
			break;
		}
		xmlDate = xmlDate->NextSiblingElement("Orders");
	}

	return xmlDate;
}


void DataHandler::saveData()
{
	string trainNumber = CustomerOrder::getTrainNumber();
	string date = CustomerOrder::getDate();

	tinyxml2::XMLDocument doc;
	doc.LoadFile("trains.xml");

	tinyxml2::XMLElement* pOrders = getDateLink(getTrain(doc, trainNumber), date);

	for (auto el : CustomerOrder::getPlaces())
	{
		pOrders->InsertEndChild(formCustomerOrder(doc, el));
	}

	doc.SaveFile("trains.xml");
}

void DataHandler::loadTrain(TrainInformation& train)
{
	loadTrain(CustomerOrder::getTrainNumber(),
	          CustomerOrder::getDate(),
	          train);
}

void DataHandler::loadRailCar(RailCarInformation& railCar)
{
	TrainInformation train;
	loadTrain(train);
	railCar = train.getRailCars()[CustomerOrder::getRailCarNumber() - 1];
}

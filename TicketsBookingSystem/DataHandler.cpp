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
		ifstream trainData("ListOfTrains.txt");

		while (trainData >> num)
		{
			bool isOk = loadTrain(num, date, train);
			if (isOk)
				trains.push_back(train);
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

void DataHandler::setTrainName(tinyxml2::XMLNode* pRoot, TrainInformation& train)
{
	train.setFullName(pRoot->FirstChildElement("FullName")->GetText());
}

void DataHandler::setTrainNumber(tinyxml2::XMLNode* pRoot, TrainInformation& train)
{
	train.setTrainNumber(pRoot->FirstChildElement("Number")->GetText());
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

void DataHandler::readOrders(tinyxml2::XMLNode* pDate,
                             vector<RailCarInformation>& RailCars)
{
	tinyxml2::XMLElement* pOrder = pDate->FirstChildElement("Order");

	while (pOrder != nullptr)
	{
		readOrder(pOrder, RailCars);

		pOrder = pOrder->NextSiblingElement("Order");
	}
}

void DataHandler::loadRailCars(tinyxml2::XMLNode* pRoot, TrainInformation& train)
{
	vector<RailCarInformation> railCars;

	tinyxml2::XMLElement* pRailCars = pRoot->FirstChildElement("RailCars");
	tinyxml2::XMLElement* pRailCar = pRailCars->FirstChildElement("RailCar");

	while (pRailCar != nullptr)
	{
		int number; string type;
		
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

	readOrders(getDateLink(pRoot, CustomerOrder::getDate()), railCars);

	train.setRailCars(railCars);
}


bool DataHandler::loadTrain(const string& num,
                            const string& date, TrainInformation& train)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile((num + ".xml").c_str());

	tinyxml2::XMLNode* pRoot = doc.FirstChild();

	vector<StationInformation> stations;
	vector<string> dates;

	getTrainStations(pRoot, stations);
	getTrainsDates(pRoot, dates);

	if (!(checkTrainByRoute(CustomerOrder::getFrom(),
		CustomerOrder::getWhere(), stations) &&
		checkTrainByTime(date, dates)))
	{
		return false;
	}
	else
	{
		setTrainName(pRoot, train);
		setTrainNumber(pRoot, train);

		train.setStations(stations);


		loadRailCars(pRoot, train);

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

void DataHandler::getTrainStations(tinyxml2::XMLNode* pRoot,
                                   vector<StationInformation>& stations)
{
	tinyxml2::XMLElement* pStations = pRoot->FirstChildElement("Stations");
	tinyxml2::XMLElement* pStation = pStations->FirstChildElement("Station");

	while (pStation != nullptr)
	{
		stations.push_back(proccesStation(pStation));
		pStation = pStation->NextSiblingElement("Station");
	}
}

void DataHandler::getTrainsDates(tinyxml2::XMLNode* pRoot,
                                 vector<string>& dates)
{
	tinyxml2::XMLElement* pDate = pRoot->FirstChildElement("Orders");

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

tinyxml2::XMLElement* DataHandler::getDateLink(tinyxml2::XMLNode* pRoot,
                                               const string& date)
{
	tinyxml2::XMLElement* xmlDate = pRoot
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
	doc.LoadFile((trainNumber + ".xml").c_str());

	tinyxml2::XMLElement* pOrders = getDateLink(doc.FirstChild(), date);

	for (auto el : CustomerOrder::getPlaces())
	{
		pOrders->InsertEndChild(formCustomerOrder(doc, el));
	}

	doc.SaveFile((trainNumber + ".xml").c_str());
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

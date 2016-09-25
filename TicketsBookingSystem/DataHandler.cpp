#include "DataHandler.h"
#include <fstream>
#include <list>

string skipSpaces(const string& str)
{
	istringstream stream(str);

	string buf;

	stream >> buf;

	return buf;
}

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
		list<string> trainNums;
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
	train.setFullName(skipSpaces(
		string(pRoot->FirstChildElement("FullName")->GetText())
			));
}

void DataHandler::setTrainNumber(tinyxml2::XMLNode* pRoot, TrainInformation& train)
{
	train.setTrainNumber(skipSpaces(
		string(pRoot->FirstChildElement("Number")->GetText())
			));
}

void DataHandler::proccesRailCarNums(const string& data, vector<size_t>& RailCarNums)
{
	std::istringstream stream(data);

	size_t num;

	while (stream >> num)
		RailCarNums.push_back(num);
}

void DataHandler::readOrder(tinyxml2::XMLNode* pOrder,
                            vector<RailCarInformation>& RailCars)
{
	SeatOrderInformation order;
	string from, where;
	size_t railCarNum, seat;

	from = pOrder->FirstChildElement("From")->GetText();
	where = pOrder->FirstChildElement("Where")->GetText();

	pOrder->FirstChildElement("RailCar")->QueryUnsignedText(&railCarNum);
	pOrder->FirstChildElement("Seat")->QueryUnsignedText(&seat);

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
	tinyxml2::XMLElement* pOrder = pDate->FirstChildElement("Orders")
	                                    ->FirstChildElement("Order");

	while (pOrder != nullptr)
	{
		readOrder(pOrder, RailCars);

		pOrder = pOrder->NextSiblingElement("Order");
	}
}

void DataHandler::loadRailCarTypes(tinyxml2::XMLNode* pRoot,
                               vector<RailCarInformation>& RailCars,
                               RailCarType type)
{
	vector<size_t> RailCarNums;
	string buffer;

	switch (type)
	{
	case RailCarType::ReservedSeat:
		buffer = pRoot
			->FirstChildElement("ReservedSeat")->GetText();
		break;
	case RailCarType::Compartment:
		buffer = pRoot
			->FirstChildElement("Compartment")->GetText();
		break;
	case RailCarType::Luxe:
		buffer = pRoot
			->FirstChildElement("Luxe")->GetText();
		break;
	}
	proccesRailCarNums(buffer, RailCarNums);

	for (auto el : RailCarNums)
	{
		RailCars.push_back(RailCarInformation(type, el));
	}
}


void DataHandler::loadRailCars(tinyxml2::XMLNode* pRoot, TrainInformation& train)
{
	vector<RailCarInformation> RailCars;

	loadRailCarTypes(pRoot, RailCars, RailCarType::ReservedSeat);
	loadRailCarTypes(pRoot, RailCars, RailCarType::Compartment);
	loadRailCarTypes(pRoot, RailCars, RailCarType::Luxe);

	sort(RailCars.begin(), RailCars.end(), *compareBySeatNum);

	train.setRailCars(RailCars);

	for (auto& el : RailCars)
	{
		el.setStations(train.getStations());
	}

	readOrders(getDateLink(pRoot, CustomerOrder::getDate()), RailCars);

	train.setRailCars(RailCars);
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
		return false;
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
	station.setName(pStation->FirstChildElement("Place")->GetText());
	station.setTimeOfArrival(pStation->FirstChildElement("Time")->GetText());

	pStation->FirstChildElement("Distance")->QueryDoubleText(&dbl_buf);

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
	tinyxml2::XMLElement* pDates = pRoot->FirstChildElement("Dates");
	tinyxml2::XMLElement* pDate = pDates->FirstChildElement("Date");

	while (pDate != nullptr)
	{
		string date;
		date = pDate->Attribute("date");
		dates.push_back(date);

		pDate = pDate->NextSiblingElement("Date");
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

	size_t RailCar = CustomerOrder::getRailCarNumber();

	tinyxml2::XMLElement* pOrder = doc.NewElement("Order");

	tinyxml2::XMLElement* pFrom = doc.NewElement("From");
	pFrom->SetText(from.c_str());

	tinyxml2::XMLElement* pWhere = doc.NewElement("Where");
	pWhere->SetText(where.c_str());

	tinyxml2::XMLElement* pRailCarNumber = doc.NewElement("RailCar");
	pRailCarNumber->SetText(RailCar);

	tinyxml2::XMLElement* pSeat = doc.NewElement("Seat");
	pSeat->SetText(place);

	pOrder->InsertEndChild(pFrom);
	pOrder->InsertEndChild(pWhere);
	pOrder->InsertEndChild(pRailCarNumber);
	pOrder->InsertEndChild(pSeat);


	return pOrder;
}

tinyxml2::XMLElement* DataHandler::getDateLink(tinyxml2::XMLNode* pRoot,
                                               const string& date)
{
	tinyxml2::XMLElement* xmlDate = pRoot
		->FirstChildElement("Dates")->FirstChildElement("Date");

	while (xmlDate != nullptr)
	{
		if (xmlDate->Attribute("date") == date)
			break;
		xmlDate = xmlDate->NextSiblingElement("Date");
	}

	return xmlDate;
}


void DataHandler::saveData()
{
	string trainNumber = CustomerOrder::getTrainNumber();
	string date = CustomerOrder::getDate();

	tinyxml2::XMLDocument doc;
	doc.LoadFile((trainNumber + ".xml").c_str());


	tinyxml2::XMLElement* pOrders = getDateLink(doc.FirstChild(), date)
		->FirstChildElement("Orders");

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
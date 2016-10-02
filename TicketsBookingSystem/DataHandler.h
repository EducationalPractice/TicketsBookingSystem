#pragma once
#include "Classes.h"
#include "tinyxml2.h"
#include <string>
#include "CustomerOrder.h"
#include <sstream>
#include <iostream>
#include <algorithm>

inline bool compareBySeatNum(const RailCarInformation& a, const RailCarInformation& b)
{
	return a.getNum() < b.getNum();
}

class DataHandler
{
private:

	static bool isBlocked(const SeatOrderInformation& order,
	                      const string& from,
	                      const string& where,
	                      const vector<StationInformation>* stations);

	static void setTrainName(tinyxml2::XMLElement* pRoot, TrainInformation& train);

	static void setTrainNumber(tinyxml2::XMLElement* pRoot, TrainInformation& train);


	static void readOrder(tinyxml2::XMLElement* pOrder,
	                      vector<RailCarInformation>& RailCars);

	static void readOrders(tinyxml2::XMLElement* pDate,
	                       vector<RailCarInformation>& RailCars);

	static void loadRailCars(tinyxml2::XMLElement* pRoot, TrainInformation& train);


	static bool loadTrain(const string& num,
	                      const string& date, TrainInformation& train);

	static bool loadTrain(tinyxml2::XMLElement* pTrain,
		const string& num,
		const string& date,
		TrainInformation& train);

	static StationInformation proccesStation(tinyxml2::XMLElement* pStation);

	static void getTrainStations(tinyxml2::XMLElement* pRoot,
	                             vector<StationInformation>& stations);

	static void getTrainsDates(tinyxml2::XMLElement* pRoot,
	                           vector<string>& dates);

	static bool checkTrainByRoute(const string& from,
	                              const string& where,
	                              const vector<StationInformation>& stations);


	static bool checkTrainByTime(string date, const vector<string>& dates);

	static void chain(vector<TrainInformation>& trains);

	static tinyxml2::XMLElement* getTrain(tinyxml2::XMLDocument& doc,
	                                      const string& num);

	static tinyxml2::XMLElement* formCustomerOrder(tinyxml2::XMLDocument& doc,
	                                               size_t place);

	static tinyxml2::XMLElement* getDateLink(tinyxml2::XMLElement* pRoot,
	                                         const string& date);


public:

	static void findSuitedTrains(vector<TrainInformation>& trains);

	static void loadTrain(TrainInformation& train);

	static void loadRailCar(RailCarInformation& railCar);

	static void saveData();


	DataHandler();
	~DataHandler();
};

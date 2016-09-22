#pragma once
#include "Classes.h"
#include "tinyxml2.h"
#include <string>

class DataHandler
{
private:
	static bool loadTrain(size_t num, string date, Train& train)
	{
		tinyxml2::XMLDocument doc;

		doc.LoadFile(to_string(num).c_str());
	}

	static const Station& proccesStation(tinyxml2::XMLElement* pStation)
	{
		Station station;

		string str_buf; int int_buf;
		
	}

	static bool checkTrain(size_t num)
	{
		tinyxml2::XMLDocument doc;

		doc.LoadFile(to_string(num).c_str());

		tinyxml2::XMLElement* pStations = doc.FirstChild()
		                                     ->FirstChildElement("Stations");
		tinyxml2::XMLElement* pStation = pStations->FirstChildElement("Station");

		vector<Station> stations;
		
		while (pStation != nullptr)
		{
			stations.push_back(proccesStation(pStation));

			pStation = pStation->NextSiblingElement("Station");
		}
	}

public:


	static vector<Train>& findSuitedTrains(string from, string where,
	                                string date, size_t num = 0)
	{
		vector<Train> trains;
		if (num != 0)
		{
			Train train;
			bool isOk = loadTrain(num, date, train);
			if (isOk)
				trains.push_back(train);
			return trains;
		}
		else
		{
		}
	}


	DataHandler();
	~DataHandler();
};

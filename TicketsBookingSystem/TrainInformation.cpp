#include "Classes.h"

int TrainInformation::getNumOfFreeSeats() const
{
	int freeSeats = 0;

	for (const auto& el : RailCars)
	{
		freeSeats += el.getNumOfFreeSeats();
	}

	return freeSeats;
}

const string& TrainInformation::getTimeOfDeparture() const
{
	string from = CustomerOrder::getFrom();

	for (const auto& el : stations)
	{
		if (from == el)
			return el.getTimeOfArrival();
	}

	return nullptr;
}

const string& TrainInformation::getTimeOfArrival() const
{
	string where = CustomerOrder::getWhere();

	for (const auto& el : stations)
	{
		if (where == el)
			return el.getTimeOfArrival();
	}

	return nullptr;
}

const vector<RailCarInformation>& TrainInformation::getRailCars() const
{
	return RailCars;
}

const string& TrainInformation::getNumber() const
{
	return number;
}

const string& TrainInformation::getFullName() const
{
	return fullName;
}

const string& TrainInformation::getDate() const
{
	return date;
}

const vector<StationInformation>& TrainInformation::getStations()
{
	return stations;
}

void TrainInformation::setFullName(string name)
{
	fullName = name;
}


void TrainInformation::setStations(vector<StationInformation>& stations)
{
	this->stations = stations;
}

void TrainInformation::setRailCars(vector<RailCarInformation>& RailCars)
{
	this->RailCars = RailCars;
}

void TrainInformation::chainRailCars()
{
	for (auto& el : RailCars)
	{
		el.setStations(stations);
	}
}

void TrainInformation::setTrainNumber(string number)
{
	this->number = number;
}

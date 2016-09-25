#include "Classes.h"


double getPricePerKM(RailCarType type)
{
	switch (type)
	{
	case RailCarType::ReservedSeat:
		return 0.1;
	case RailCarType::Compartment:
		return 0.15;
	case RailCarType::Luxe:
		return 0.25;
	}
}

size_t getTotalNumOfSeats(RailCarType type)
{
	switch (type)
	{
	case RailCarType::ReservedSeat:
		return 54;
	case RailCarType::Compartment:
		return 36;
	case RailCarType::Luxe:
		return 18;
	}
}

double StationInformation::getDistance() const
{
	return distanceFromFirst;
}

const string& StationInformation::getTimeOfArrival() const
{
	return timeOfArrival;
}


void StationInformation::setName(const string& name)
{
	this->name = name;
}

void StationInformation::setTimeOfArrival(const string& time)
{
	this->timeOfArrival = time;
}

void StationInformation::setDistance(double distance)
{
	this->distanceFromFirst = distance;
}

bool operator==(string str, const StationInformation& station)
{
	return str == station.name;
}

bool operator==(const StationInformation& station, string str)
{
	return str == station;
}

const string& SeatOrderInformation::getFrom() const
{
	return from;
}

const string& SeatOrderInformation::getWhere() const
{
	return where;
}

size_t SeatOrderInformation::getSeatNum() const
{
	return seatNum;
}

void SeatOrderInformation::setFrom(const string& from)
{
	this->from = from;
}

void SeatOrderInformation::setWhere(const string& where)
{
	this->where = where;
}

void SeatOrderInformation::setSeatNum(size_t seat_num)
{
	seatNum = seat_num;
}

RailCarInformation::RailCarInformation()
{
}

RailCarInformation::RailCarInformation(RailCarType type, size_t number) :
	type(type), number(number)
{
}


double RailCarInformation::getTicketPrice() const
{
	string from = CustomerOrder::getFrom();
	string where = CustomerOrder::getWhere();

	double f = 0, s = 0;


	for (const auto& el : *stations)
	{
		if (from == el)
			f = el.getDistance();
		if (where == el)
			s = el.getDistance();
	}

	return (s - f) * getPricePerKM(type);
}


int RailCarInformation::getNumOfFreeSeats() const
{
	return getTotalNumOfSeats(type) - bookedSeats.size();
}

vector<size_t> RailCarInformation::getBookedSeats() const
{
	return bookedSeats;
}


void RailCarInformation::setStations(const vector<StationInformation>& stations)
{
	this->stations = &stations;
}

void RailCarInformation::setType(RailCarType type)
{
	this->type = type;
}

void RailCarInformation::setNum(size_t number)
{
	this->number = number;
}

size_t RailCarInformation::getNum() const
{
	return number;
}

const vector<StationInformation>* RailCarInformation::getStations() const
{
	return stations;
}

void RailCarInformation::addBookedSeat(size_t num)
{
	bookedSeats.push_back(num);
}

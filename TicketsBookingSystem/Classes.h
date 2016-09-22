#pragma once
#include <vector>

using namespace std;


class Station
{
	string name;
	string timeOfArrival;
	double distanceFromFirst;

public:

	double getDistance() const
	{
		return distanceFromFirst;
	}


	void setName(const string& name)
	{
		this->name = name;
	}

	void setTimeOfArrival(const string& time)
	{
		this->timeOfArrival = time;
	}

	void setDistance(double distance)
	{
		this->distanceFromFirst = distance;
	}

	friend bool operator==(string str, const Station& station)
	{
		return str == station.name;
	}

	friend bool operator==(const Station& station, string str)
	{
		return str == station;
	}
};

class SeatOrder
{
	string from;
	string where;

	size_t place;
public:

	const string& getFrom() const
	{
		return from;
	}

	const string& getWhere() const
	{
		return where;
	}
};

enum class CarType
{
	ReservedSeat,
	Compartment,
	Luxe
};

double getPricePerKM(CarType type)
{
	switch (type)
	{
	case CarType::ReservedSeat:
		return 0.1;
	case CarType::Compartment:
		return 0.15;
	case CarType::Luxe:
		return 0.25;
	}
}

class Car
{
	CarType type;
	size_t number;

	size_t totalNumOfSeats;
	vector<SeatOrder> bookedSeats;

	vector<Station>* stations;

	bool isBlocked(const SeatOrder& order, string from, string where) const
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
		
		return aj <= bi || bj <= ai;
	}

public:

	double getPrice(string from, string where) const
	{
		double f = 0, s = 0;
		for (const auto& el: *stations)
		{
			if (from == el)
				f = el.getDistance();
			if (where == el)
				s = el.getDistance();
		}

		return (s - f)* getPricePerKM(type);
	}

	vector<SeatOrder> getBlockedOrders(string from, string where)
	{
		vector<SeatOrder> blockedSeats;
		
		for (auto& el : bookedSeats)
		{
			if (isBlocked(el, from, where))
				blockedSeats.push_back(el);
		}
		
		return blockedSeats;
	}

	int getNumOfFreeSeats(string from, string where) const
	{
		int blockedSeats = 0;

		for (const auto& el: bookedSeats)
		{
			if (isBlocked(el, from, where))
				blockedSeats++;
		}
		return totalNumOfSeats - blockedSeats;
	}

	void setStations(vector<Station>& stations)
	{
		this->stations = &stations;
	}

	void setType(CarType type)
	{
		this->type = type;
	}

	void setNum(size_t number)
	{
		this->number = number;
	}

	void addOrder(SeatOrder& order)
	{
		bookedSeats.push_back(order);
	}
};

class Train
{
	size_t number;
	string fullName;
	string date;
	vector<Station> stations;
	vector<Car> cars;
public:

	int getNumOfFreeSeats(string from, string where) const
	{
		int freeSeats = 0;
		
		for (const auto& el: cars)
		{
			freeSeats += el.getNumOfFreeSeats(from, where);
		}

		return freeSeats;
	}

	size_t getNumber() const
	{
		return number;
	}

	const string& getFullName() const
	{
		return fullName;
	}

	const string& getDate() const
	{
		return date;
	}
};

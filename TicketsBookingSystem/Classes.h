#pragma once
#include <vector>
#include "CustomerOrder.h"
#include <iostream>

using namespace std;


enum class RailCarType
{
	ReservedSeat,
	Compartment,
	Luxe
};

double getPricePerKM(RailCarType type);

size_t getTotalNumOfSeats(RailCarType type);

class StationInformation
{
	string name;
	string timeOfArrival;
	double distanceFromFirst;

public:

	double getDistance() const;

	const string& getTimeOfArrival() const;


	void setName(const string& name);

	void setTimeOfArrival(const string& time);

	void setDistance(double distance);

	friend bool operator==(string str, const StationInformation& station);

	friend bool operator==(const StationInformation& station, string str);
};

class SeatOrderInformation
{
	string from;
	string where;

	size_t seatNum;
public:

	const string& getFrom() const;

	const string& getWhere() const;

	size_t getSeatNum() const;


	void setFrom(const string& from);
	void setWhere(const string& where);
	void setSeatNum(size_t seat_num);
};


class RailCarInformation
{
	RailCarType type;
	size_t number;

	vector<size_t> bookedSeats;

	const vector<StationInformation>* stations;

public:
	RailCarInformation();

	explicit RailCarInformation(RailCarType type, size_t number);

	double getTicketPrice() const;

	int getNumOfFreeSeats() const;

	vector<size_t> getBookedSeats() const;
	
	size_t getNum() const;


	//DON'T USE FUNCTIONS BELOW. THEY ARE FOR INTERNAL USE
	void setStations(const vector<StationInformation>& stations);

	void setType(RailCarType type);

	void setNum(size_t number);

	const vector<StationInformation>* getStations() const;

	void addBookedSeat(size_t num);

};

class TrainInformation
{
	string number;
	string fullName;

	string date;

	vector<StationInformation> stations;
	vector<RailCarInformation> RailCars;
public:

	int getNumOfFreeSeats() const;

	const string& getTimeOfDeparture() const;

	const string& getTimeOfArrival() const;

	const vector<RailCarInformation>& getRailCars() const;

	const string& getNumber() const;

	const string& getFullName() const;

	const string& getDate() const;

	//DON'T USE FUNCTIONS BELOW. THEY ARE FOR INTERNAL USE
	const vector<StationInformation>& getStations();

	void setFullName(const string& name);

	void setStations(vector<StationInformation>& stations);

	void setRailCars(vector<RailCarInformation>& RailCars);

	void chainRailCars();

	void setTrainNumber(const string& number);
};

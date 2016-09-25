#pragma once
#include <string>
#include <vector>

using namespace std;

class CustomerOrder
{
private:
	string where;
	string from;

	string date;

	string trainNumber;
	size_t RailCarNumber;
	vector<size_t> places;

	double price;

	CustomerOrder();

	static CustomerOrder* order;
public:


	static string getWhere();
	static void setWhere(const string& where);
	
	static string getFrom();
	static void setFrom(const string& from);
	
	static string getDate();
	static void setDate(const string& date);
	
	static const string& getTrainNumber();
	static void setTrainNumber(const string& train_number);
	
	static size_t getRailCarNumber();
	static void setRailCarNumber(size_t RailCar_number);
	
	static const vector<size_t>& getPlaces();
	static void setPlaces(const vector<size_t>& place_number);
	
	static double getPrice();
	static void setPrice(double price);
};

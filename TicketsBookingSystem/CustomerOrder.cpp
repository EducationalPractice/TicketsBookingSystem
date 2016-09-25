#include "CustomerOrder.h"

using namespace std;

CustomerOrder* CustomerOrder::order = new CustomerOrder();

CustomerOrder::CustomerOrder()
{
	trainNumber = "";
}

string CustomerOrder::getWhere()
{
	return order->where;
}

void CustomerOrder::setWhere(const string& where)
{
	order->where = where;
}

string CustomerOrder::getFrom()
{
	return order->from;
}

void CustomerOrder::setFrom(const string& from)
{
	order->from = from;
}

string CustomerOrder::getDate()
{
	return order->date;
}

void CustomerOrder::setDate(const string& date)
{
	order->date = date;
}

const string& CustomerOrder::getTrainNumber()
{
	return order->trainNumber;
}

void CustomerOrder::setTrainNumber(const string& train_number)
{
	order->trainNumber = train_number;
}

size_t CustomerOrder::getRailCarNumber()
{
	return order->RailCarNumber;
}

void CustomerOrder::setRailCarNumber(size_t RailCar_number)
{
	order->RailCarNumber = RailCar_number;
}

const vector<size_t>& CustomerOrder::getPlaces()
{
	return order->places;
}

void CustomerOrder::setPlaces(const vector<size_t>& places)
{
	order->places = places;
}

double CustomerOrder::getPrice()
{
	return order->price;
}

void CustomerOrder::setPrice(double price)
{
	order->price = price;
}

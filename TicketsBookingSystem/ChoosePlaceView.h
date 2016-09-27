#pragma once
#include <vector>
#include "Classes.h"
#include "Printer.h"
#include "Views.h"
#include "ConsoleFunctions.h"

using namespace std;

class CarView : public View
{
	RailCarInformation railCar;
public:
	CarView();
	void printReserved();
	void handleReserved(size_t&, HDC);
	void printCompartment();
	void handleCompartment(size_t&, HDC);
	void printLuxe();
	void handleLuxe(size_t&, HDC);
	void draw();
	View* handle();
};
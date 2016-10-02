#pragma once
#include <vector>
#include "Classes.h"
#include "Printer.h"
#include "Views.h"
#include "ConsoleFunctions.h"

using namespace std;

class CoachView : public View
{
	TrainInformation inf;
	int IsSelected = 0;

	void drawTrains(size_t qntOfCars);
	
public:
	CoachView();
	
	void draw();
	void drawMenu(int x, int y,int x1,int y1);
	View* handle();
};
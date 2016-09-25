#pragma once
#include <vector>
#include "Classes.h"
#include "Printer.h"

class View
{
public:
	virtual void draw() = 0;
	virtual View* handle() = 0;
};

class StartView : public View
{
private:
	string where;
	string from;
	string date;
	bool fromEntered = false;
	bool whereEntered = false;
	bool dateEntered = false;
	int counter = 0;
	bool checkIfDateIsOk(string date);
	void enterLine(string& city, bool & isEntered,int maxLength, int& counter);
public:
	StartView();
	void draw();
	View* handle();
};

class TableView : public View
{
private:
	vector<TrainInformation> trains;
	int selectedOption = 0;
	void drawLine(Printer printer, int i, TrainInformation currentTrain);
public:
	TableView();
	void draw();
	View* handle();
};

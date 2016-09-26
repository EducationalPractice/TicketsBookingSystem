#include "Views.h"
#include "DataHandler.h"
#include "CustomerOrder.h"
#include "ConsoleFunctions.h"
#include <conio.h>

TableView::TableView()
{
	DataHandler::findSuitedTrains(trains);
}

void TableView::drawLine(Printer printer, int i, TrainInformation currentTrain)
{
	setCursoreAtPosition(2, i * 2 + 8);
	printer.print(currentTrain.getNumber());
	setCursoreAtPosition(9, i * 2 + 8);
	if (currentTrain.getFullName().length() > 12)
	{
		printer.print(currentTrain.getFullName().substr(0, 12));
	}
	else
	{
		printer.print(currentTrain.getFullName());
	}
	setCursoreAtPosition(26, i * 2 + 8);
	printer.print(currentTrain.getTimeOfDeparture());
	setCursoreAtPosition(36, i * 2 + 8);
	printer.print(currentTrain.getTimeOfArrival());
	setCursoreAtPosition(49, i * 2 + 8);
	printer.print(to_string(currentTrain.getNumOfFreeSeats()));
	cout << endl;
}

void TableView::draw()
{
	Printer printer(Color::High_intensity_white, Color::Blue);
	Printer _printer(Color::High_intensity_white, Color::Yellow);
	printAtCenterOfLine(5, "#      Name          Departure Arrival    Free Places", printer);
	for (int i = 0; i < trains.size(); ++i)
	{
		TrainInformation currentTrain = trains[i];
		if (selectedOption == i)
		{
			drawLine(_printer, i, currentTrain);
			SetConsoleTextAttribute(hConOut, ((int)Color::High_intensity_white + (int)Color::Blue) * 16);
		}
		else
		{
			drawLine(printer, i, currentTrain);
		}
	}
}

View* TableView::handle()
{
	View* newView = this;
	int key = _getch();
	switch (key)
	{
	case KEY_DOWN:
	{
		if (selectedOption != trains.size() - 1)
		{
			++selectedOption;
		}
		else
		{
			selectedOption = 0;
		}
		break;
	}
	case KEY_UP:
	{
		if (selectedOption == 0)
		{
			selectedOption = trains.size() - 1;
		}
		else
		{
			--selectedOption;
		}
		break;
	}
	case KEY_ENTER:
	{
		CustomerOrder::setTrainNumber(trains[selectedOption].getNumber());
		//HERE MUST BE THIRD VIEW, NOT STARTVIEW
		newView = new StartView();
	}
	}
	return newView;
}
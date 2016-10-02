#include "Views.h"
#include "DataHandler.h"
#include "CustomerOrder.h"
#include "ConsoleFunctions.h"
#include <conio.h>
#include "CoachView.h"

TableView::TableView()
{
	DataHandler::findSuitedTrains(trains);
}

void TableView::drawLine(Printer printer, int i, TrainInformation currentTrain)
{
	setCursoreAtPosition(12, i * 2 + 8);
	printer.print(currentTrain.getNumber());
	setCursoreAtPosition(23, i * 2 + 8);
	if (currentTrain.getFullName().length() > 12)
	{
		printer.print(currentTrain.getFullName().substr(0, 15));
	}
	else
	{
		printer.print(currentTrain.getFullName());
	}
	setCursoreAtPosition(43, i * 2 + 8);
	printer.print(currentTrain.getTimeOfDeparture());
	setCursoreAtPosition(53, i * 2 + 8);
	printer.print(currentTrain.getTimeOfArrival());
	setCursoreAtPosition(66, i * 2 + 8);
	printer.print(to_string(currentTrain.getNumOfFreeSeats()));
	cout << endl;
}

void TableView::draw()
{
	Printer printer(Color::High_intensity_white, Color::Blue);
	Printer _printer(Color::Black, Color::Yellow);
	printAtCenterOfLine(5, "Number of train     Name           Departure  Arrival    Free Places", printer);
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
	printAtCenterOfLine(28, "Press ESC to exit", printer);
	
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
		newView = new CoachView();
		break;
	}
	case KEY_ESCAPE:
		newView = NULL;
	}
	return newView;
}
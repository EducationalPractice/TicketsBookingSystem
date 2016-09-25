#include "Views.h"
#include "Printer.h"
#include "ConsoleFunctions.h"
#include "CustomerOrder.h"
#include <iostream>
#include <conio.h>
#include "ConsoleFunctions.h"

using namespace std;

StartView::StartView() {}

void StartView::draw()
{
	Printer printer(Color::High_intensity_white, Color::Blue);
	printAtCenterOfLine(2, "Welcome to the ticket booking system!", printer);
	printAtCenterOfLine(3, "Please, enter:", printer);
	setCursoreAtPosition(10, 8);
	printer.print("From:");
	setCursoreAtPosition(10, 11);
	printer.print("Where:");
	setCursoreAtPosition(10, 14);
	printer.print("Date:");
	setCursoreAtPosition(16, 8);
	printer.print(from);
	setCursoreAtPosition(17, 11);
	printer.print(where);
	setCursoreAtPosition(16, 14);
	printer.print(date);
}

bool StartView::checkIfDateIsOk(string date)
{
	if ((char)date[0] >= '0' && (char)date[0] <= '9' &&
		(char)date[1] >= '0' && (char)date[1] <= '9' &&
		(char)date[2] >= '0' && (char)date[2] <= '9' &&
		(char)date[3] >= '0' && (char)date[3] <= '9' &&
		(char)date[5] >= '0' && (char)date[5] <= '9' &&
		(char)date[6] >= '0' && (char)date[6] <= '9' &&
		(char)date[8] >= '0' && (char)date[8] <= '9' &&
		(char)date[9] >= '0' && (char)date[9] <= '9' &&
		(char)date[4] == '.' && (char)date[7] == '.')
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StartView::enterLine(string& word, bool & isEntered, int maxLength, int& counter)
{
	int key = _getch();
	if (counter == maxLength)
	{
		isEntered = true;
		counter = 0;
	}
	else if (key == KEY_ENTER && word.size() != 0) 
	{
		isEntered = true;
		counter = 0;
	}
	else if (key == KEY_BACKSPACE && word.size() != 0)
	{
		string temp = "";
		for (size_t i = 0; i < word.length() - 1; i++)
		{
			temp += word[i];
		}
		word = temp;
		--counter;
	}
	else if (counter != maxLength)
	{
		word += (char)key;
		++counter;
	}

}



View* StartView::handle()
{
	View* newView = this;
	if (!fromEntered)
	{
		enterLine(from, fromEntered, 13, counter);
	}
	if (fromEntered == true)
	{
		CustomerOrder::setFrom(from);
		if (!whereEntered)
		{
			enterLine(where, whereEntered, 13, counter);
		}
		if (whereEntered == true)
		{
		CustomerOrder::setWhere(where);
		enterLine(date, dateEntered, 11, counter);
		if (dateEntered)
		{
			if (checkIfDateIsOk(date))
			{
				CustomerOrder::setDate(date);
				newView = new TableView();
			}
			else
			{
				dateEntered = false;
				Printer printer(Color::High_intensity_white, Color::Blue);
				printAtCenterOfLine(20, "Bad date, try again. Must be XXXX.YY.ZZ.", printer);
				system("PAUSE");
				date = "";
			}
		}

		}
	}
	return newView;
}
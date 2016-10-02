#include <conio.h>
#include "PaymentView.h"
#include "DataHandler.h"
#include "ConsoleFunctions.h"
#include "Printer.h"
PaymentView::PaymentView()
{
}

void PaymentView::setCreditCard(string cc)
{
	creditCard = cc;
}

void PaymentView::setDateOfExpire(string doe)
{
	dateOfExpire = doe;
}

void PaymentView::setCVV(string _cvv)
{
	CVV = _cvv;
}

void PaymentView::draw()
{
	Printer printer(Color::High_intensity_white, Color::Blue);
	printAtCenterOfLine(2, "Welcome to the ticket booking system!", printer);
	printAtCenterOfLine(3, "Please, enter:", printer);
	setCursoreAtPosition(20, 8);
	printer.print("Credit Card:");
	setCursoreAtPosition(20, 11);
	printer.print("Date of Expire:");
	setCursoreAtPosition(20, 14);
	printer.print("CVV:");
	setCursoreAtPosition(26, 8);
	setCursoreAtPosition(27, 11);
	setCursoreAtPosition(26, 14);
	
}

void PaymentView::enterLine(string& word, bool & isEntered, int maxLength, int& counter)
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
	else if (counter != maxLength &&
		((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || key == '.' || key == '-'))
	{
		word += (char)key;
		++counter;
	}
}



View* PaymentView::handle()
{
	View* newView = this;
	if (!creditcard_entered)
	{
		enterLine(creditCard, creditcard_entered, 13, counter);
	}
	if (creditcard_entered == true)
	{
		setCreditCard(creditCard);
		if (!dateOfExpire_entered)
		{
			enterLine(dateOfExpire, dateOfExpire_entered, 13, counter);
		}
		if (dateOfExpire_entered == true)
		{
			setDateOfExpire(dateOfExpire);
			enterLine(dateOfExpire, dateOfExpire_entered, 11, counter);
			if (dateOfExpire_entered)
			{
				newView = this;
			}

		}
	}
	return newView;
}

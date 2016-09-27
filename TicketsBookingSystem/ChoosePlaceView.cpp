#include "ChoosePlaceView.h"
#include "DataHandler.h"
#include <conio.h>
#include "CustomerOrder.h"

using namespace std;

CarView::CarView()
{
	DataHandler::loadRailCar(railCar);
}

void drawBox(int x, int y, HDC hdc, bool booked)
{
	int k = 0;
	int g = 0;
	HPEN penFree(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
	HPEN penBooked(CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
	HGDIOBJ currentPen;
	if (booked)
		currentPen =(HPEN)SelectObject(hdc, penBooked);
	else
		currentPen = (HPEN)SelectObject(hdc, penFree);
	MoveToEx(hdc, x, y, NULL);
	k += 12;
	LineTo(hdc, x + k, y + g);
	g += 12;
	LineTo(hdc, x + k, y + g);
	k -= 12;
	LineTo(hdc, x + k, y + g);
	g -= 12;
	LineTo(hdc, x + k, y + g);
	MoveToEx(hdc, x, y, NULL);
	k = 0;
	for (size_t i = 0; i < 6; i++)
	{
		MoveToEx(hdc, x + k, y, NULL);
		k += 2;
		LineTo(hdc, x + k, y + 12);
	}
	currentPen = (HPEN)SelectObject(hdc, (CreatePen(PS_SOLID, 3, RGB(255, 255, 255))));
}
void drawSelectedSeat(int x, int y, HDC hdc)
{
	int k = 0;
	int g = 0;
	MoveToEx(hdc, x, y, NULL);
	k += 12;
	LineTo(hdc, x + k, y + g);
	g += 12;
	LineTo(hdc, x + k, y + g);
	k -= 12;
	LineTo(hdc, x + k, y + g);
	g -= 12;
	LineTo(hdc, x + k, y + g);

}
void CarView::printReserved()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen(CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
	HPEN penFreeSeats(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
	HPEN penBookedSeats(CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	vector<size_t> bookedSeats = railCar.getBookedSeats();

	MoveToEx(hdc, 50, 250, NULL);
	LineTo(hdc, 100, 270);
	LineTo(hdc, 700, 270);
	LineTo(hdc, 750, 250);
	MoveToEx(hdc, 50, 280, NULL);
	LineTo(hdc, 100, 300);
	LineTo(hdc, 700, 300);
	LineTo(hdc, 750, 280);

	MoveToEx(hdc, 100, 150, NULL);
	LineTo(hdc, 100, 270);
	MoveToEx(hdc, 100, 300, NULL);
	LineTo(hdc, 100, 350);

	MoveToEx(hdc, 166, 150, NULL);
	LineTo(hdc, 166, 270);
	MoveToEx(hdc, 166, 300, NULL);
	LineTo(hdc, 166, 350);

	MoveToEx(hdc, 233, 150, NULL);
	LineTo(hdc, 233, 270);
	MoveToEx(hdc, 233, 300, NULL);
	LineTo(hdc, 233, 350);

	MoveToEx(hdc, 298, 150, NULL);
	LineTo(hdc, 298, 270);
	MoveToEx(hdc, 298, 300, NULL);
	LineTo(hdc, 298, 350);

	MoveToEx(hdc, 365, 150, NULL);
	LineTo(hdc, 365, 270);
	MoveToEx(hdc, 365, 300, NULL);
	LineTo(hdc, 365, 350);

	MoveToEx(hdc, 430, 150, NULL);
	LineTo(hdc, 430, 270);
	MoveToEx(hdc, 430, 300, NULL);
	LineTo(hdc, 430, 350);

	MoveToEx(hdc, 497, 150, NULL);
	LineTo(hdc, 497, 270);
	MoveToEx(hdc, 497, 300, NULL);
	LineTo(hdc, 497, 350);

	MoveToEx(hdc, 562, 150, NULL);
	LineTo(hdc, 562, 270);
	MoveToEx(hdc, 562, 300, NULL);
	LineTo(hdc, 562, 350);

	MoveToEx(hdc, 628, 150, NULL);
	LineTo(hdc, 628, 270);
	MoveToEx(hdc, 628, 300, NULL);
	LineTo(hdc, 628, 350);

	MoveToEx(hdc, 700, 150, NULL);
	LineTo(hdc, 700, 270);
	MoveToEx(hdc, 700, 300, NULL);
	LineTo(hdc, 700, 350);

	currentPen = (HPEN)SelectObject(hdc, penFreeSeats);
	int k = 0;
	int startX = 110;
	for (size_t j = 0; j < 18; j++)
	{
		drawBox(startX + k, 175, hdc, false);
		if (j % 2 == 1)
		{
			k += 6;
		}
		k += 30;
	}
	k = 0;
	for (size_t j = 0; j < 18; j++)
	{
		drawBox(startX + k, 230, hdc, false);
		if (j % 2 == 1)
		{
			k += 6;
		}
		k += 30;
	}
	k = 0;
	for (size_t j = 0; j < 18; j++)
	{
		drawBox(startX + k, 325, hdc, false);
		if (j % 2 == 1)
		{
			k += 6;
		}
		k += 30;
	}
	k = 0;
	size_t tmpBookedSeat;
	currentPen = (HPEN)SelectObject(hdc, penBookedSeats);
	for (size_t i = 0; i < bookedSeats.size(); i++)
	{
		tmpBookedSeat = bookedSeats[i];
		for (size_t j = 0; j < 18; j++)
		{
			if (tmpBookedSeat % 2 == 0 && tmpBookedSeat % 6 != 0 && tmpBookedSeat == (j + 1) * 2 + (j + 1) - 1 && j % 2 == 0)
			{
				drawBox(startX + k, 230, hdc, true);
			}
			else if (tmpBookedSeat % 2 == 0 && tmpBookedSeat % 6 != 0 && tmpBookedSeat == (j + 1) * 2 + (j + 1) - 2 && j % 2 == 1)
			{
				drawBox(startX + k, 230, hdc, true);
			}

			if (tmpBookedSeat % 2 == 1 && tmpBookedSeat == (j + 1) * 2 + (j + 1) - 2 && j % 2 == 0)
			{
				drawBox(startX + k, 175, hdc, true);
			}
			else if (tmpBookedSeat % 2 == 1 && tmpBookedSeat == (j + 1) * 2 + (j + 1) - 3 && j % 2 == 1)
			{
				drawBox(startX + k, 175, hdc, true);
			}

			if (tmpBookedSeat == (j + 1) * 3 + 2 && j % 2 == 0)
			{
				drawBox(startX + k, 325, hdc, true);
			}
			else if  (tmpBookedSeat == (j + 1) * 3 && j % 2 == 1)
			{
				drawBox(startX + k, 325, hdc, true);
			}
			if (j % 2 == 1)
			{
				k += 6;
			}
			k += 30;
		}
		k = 0;
	}

}
void CarView::draw()
{
	Printer printer(Color::High_intensity_white, Color::Blue);

	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen(CreatePen(PS_SOLID, 3, RGB(255,255,255)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	printAtCenterOfLine(3, "This is railcar # ", printer);
	setCursoreAtPosition(50, 3);
	cout << railCar.getNum();
	printAtCenterOfLine(5, "Please choose place", printer);

	MoveToEx(hdc, 100, 150, NULL);
	LineTo(hdc, 700, 150);
	LineTo(hdc, 750, 200);
	LineTo(hdc, 750, 300);
	LineTo(hdc, 700, 350);
	LineTo(hdc, 100, 350);
	LineTo(hdc, 50, 300);
	LineTo(hdc, 50, 200);
	LineTo(hdc, 100, 150);
	switch (railCar.getType())
	{
	case RailCarType::ReservedSeat:
		printReserved();
		break;
	case RailCarType::Compartment:
		printCompartment();
		break;
	case RailCarType::Luxe:
		printLuxe();
		break;
	}
}
void CarView::handleReserved(size_t& place, HDC hdc)
{
	place = 0;

	vector<size_t> bookedSeats = railCar.getBookedSeats();

	int x = 0;
	int oldX = x;
	int y = 0;
	int oldY = y;

	int numX = 1;
	int numY = 0;

	drawSelectedSeat(110, 175, hdc);
	int k = _getch();
	bool choose = false;
	size_t tmpBookedSeat;
	size_t index = 0;
	bool booked = false;
	while (!choose)
	{
		drawBox(110 + oldX, 175 + oldY, hdc, booked);
		booked = false;
		for (size_t i = 0; i < bookedSeats.size(); i++)
		{
			tmpBookedSeat = bookedSeats[i];
			if (numY == 1)
			{
				if (tmpBookedSeat == numX * 2 + numX - 1 && numX % 2 == 1)
				{
					booked = true;
					break;
				}
				else if (tmpBookedSeat == numX * 2 + numX - 2 && numX % 2 == 0)
				{
					booked = true;
					break;
				}
			}
			else if (numY == 0)
			{
				if (tmpBookedSeat == numX * 2 + numX - 2 && numX % 2 == 1)
				{
					booked = true;
					break;
				}
				else if (tmpBookedSeat == numX * 2 + numX - 3 && numX % 2 == 0)
				{
					booked = true;
					break;
				}
			}
			else if (numY == 2)
			{
				if (tmpBookedSeat == numX * 3 + 2 && numX % 2 == 1)
				{
					booked = true;
					break;
				}
				else if (tmpBookedSeat == numX * 3 && numX % 2 == 0)
				{
					booked = true;
					break;
				}
			}
		}

		oldX = x;
		oldY = y;
		drawSelectedSeat(110 + x, 175 + y, hdc);
		k = _getch();
		switch (k)
		{
		case KEY_RIGHT:
			if (numX % 2 == 0 && x < 550)
				x += 6;
			if (x < 550)
			{
				x += 30;
				numX++;
			}
			break;
		case KEY_LEFT:
			if (numX % 2 == 1 && x > 0)
				x -= 6;
			if (x > 0)
			{
				x -= 30;
				numX--;
			}
			break;
		case KEY_DOWN:
			numY++;
			break;
		case KEY_UP:
			numY--;
			break;
		case KEY_ENTER:
			choose = true;
			if (numY == 0)
			{
				if (numX % 2 == 0)
					place = numX * 2 + numX - 3;
				else
					place = numX * 2 + numX - 2;
			}
			else if (numY == 1)
			{
				if (numX % 2 == 0)
					place = numX * 2 + numX - 2;
				else
					place = numX * 2 + numX - 1;
			}
			else if (numY == 2)
			{
				if (numX % 2 == 1)
					place = numX * 3 + 2;
				else
					place = numX * 3;
			}
		}

		if (numY == 0)
			y = 0;
		else if (numY == 1)
			y = 55;
		else if (numY == 2)
			y = 150;
		else if (numY == 3)
			numY = 2;
		else if (numY == -1)
			numY = 0;

		bool needToWrite = false;
		for (size_t i = 0; i < bookedSeats.size(); i++)
		{
			if (place == bookedSeats[i])
			{
				choose = false;
				needToWrite = true;
			}
		}
		if (needToWrite)
			printAtCenterOfLine(25, "This place is already booked. Choose another.", Printer(Color::High_intensity_white, Color::Blue));
	}
}
void CarView::printCompartment()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen(CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
	HPEN penFreeSeats(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
	HPEN penBookedSeats(CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	vector<size_t> bookedSeats = railCar.getBookedSeats();

	MoveToEx(hdc, 50, 250, NULL);
	LineTo(hdc, 100, 270);
	LineTo(hdc, 700, 270);
	LineTo(hdc, 750, 250);
	MoveToEx(hdc, 50, 280, NULL);

	MoveToEx(hdc, 100, 150, NULL);
	LineTo(hdc, 100, 270);

	MoveToEx(hdc, 166, 150, NULL);
	LineTo(hdc, 166, 270);

	MoveToEx(hdc, 233, 150, NULL);
	LineTo(hdc, 233, 270);

	MoveToEx(hdc, 298, 150, NULL);
	LineTo(hdc, 298, 270);

	MoveToEx(hdc, 365, 150, NULL);
	LineTo(hdc, 365, 270);

	MoveToEx(hdc, 430, 150, NULL);
	LineTo(hdc, 430, 270);

	MoveToEx(hdc, 497, 150, NULL);
	LineTo(hdc, 497, 270);

	MoveToEx(hdc, 562, 150, NULL);
	LineTo(hdc, 562, 270);

	MoveToEx(hdc, 628, 150, NULL);
	LineTo(hdc, 628, 270);

	MoveToEx(hdc, 700, 150, NULL);
	LineTo(hdc, 700, 270);

	currentPen = (HPEN)SelectObject(hdc, penFreeSeats);
	int k = 0;
	int startX = 110;
	for (size_t j = 0; j < 18; j++)
	{
		drawBox(startX + k, 175, hdc, false);
		if (j % 2 == 1)
		{
			k += 6;
		}
		k += 30;
	}
	k = 0;
	for (size_t j = 0; j < 18; j++)
	{
		drawBox(startX + k, 230, hdc, false);
		if (j % 2 == 1)
		{
			k += 6;
		}
		k += 30;
	}
	k = 0;
	size_t tmpBookedSeat;
	currentPen = (HPEN)SelectObject(hdc, penBookedSeats);
	for (size_t i = 0; i < bookedSeats.size(); i++)
	{
		tmpBookedSeat = bookedSeats[i];
		for (size_t j = 0; j < 18; j++)
		{
			if (tmpBookedSeat % 2 == 0 && tmpBookedSeat == (j + 1) * 2)
			{
				drawBox(startX + k, 230, hdc, true);
			}
			if (tmpBookedSeat % 2 == 1 && tmpBookedSeat == (j + 1) * 2 - 1)
			{
				drawBox(startX + k, 175, hdc, true);
			}

			if (j % 2 == 1)
			{
				k += 6;
			}
			k += 30;
		}
		k = 0;
	}

}
void CarView::handleCompartment(size_t &place, HDC hdc)
{
	place = 0;

	vector<size_t> bookedSeats = railCar.getBookedSeats();

	int x = 0;
	int oldX = x;
	int y = 0;
	int oldY = y;

	int numX = 1;
	int numY = 0;

	drawSelectedSeat(110, 175, hdc);
	int k = _getch();
	bool choose = false;
	size_t tmpBookedSeat;
	size_t index = 0;
	bool booked = false;
	while (!choose)
	{
		drawBox(110 + oldX, 175 + oldY, hdc, booked);
		booked = false;
		for (size_t i = 0; i < bookedSeats.size(); i++)
		{
			tmpBookedSeat = bookedSeats[i];
			if (numY == 1)
			{
				if (tmpBookedSeat == numX * 2)
				{
					booked = true;
					break;
				}
			}
			else if (numY == 0)
			{
				if (tmpBookedSeat == numX * 2 - 1)
				{
					booked = true;
					break;
				}
			}
		}

		oldX = x;
		oldY = y;
		drawSelectedSeat(110 + x, 175 + y, hdc);
		k = _getch();
		switch (k)
		{
		case KEY_RIGHT:
			if (numX % 2 == 0 && x < 550)
				x += 6;
			if (x < 550)
			{
				x += 30;
				numX++;
			}
			break;
		case KEY_LEFT:
			if (numX % 2 == 1 && x > 0)
				x -= 6;
			if (x > 0)
			{
				x -= 30;
				numX--;
			}
			break;
		case KEY_DOWN:
			numY++;
			break;
		case KEY_UP:
			numY--;
			break;
		case KEY_ENTER:
			choose = true;
			if (numY == 0)
			{
				place = numX * 2 - 1;
			}
			else if (numY == 1)
			{
				place = numX * 2;
			}
		}

		if (numY == 0)
			y = 0;
		else if (numY == 1)
			y = 55;
		else if (numY == 2)
			numY = 1;
		else if (numY == -1)
			numY = 0;

		bool needToWrite = false;
		for (size_t i = 0; i < bookedSeats.size(); i++)
		{
			if (place == bookedSeats[i])
			{
				choose = false;
				needToWrite = true;
			}
		}
		if (needToWrite)
			printAtCenterOfLine(25, "This place is already booked. Choose another.", Printer(Color::High_intensity_white, Color::Blue));
	}
}
void CarView::printLuxe()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen(CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
	HPEN penFreeSeats(CreatePen(PS_SOLID, 3, RGB(0, 255, 0)));
	HPEN penBookedSeats(CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	vector<size_t> bookedSeats = railCar.getBookedSeats();

	MoveToEx(hdc, 50, 250, NULL);
	LineTo(hdc, 100, 270);
	LineTo(hdc, 700, 270);
	LineTo(hdc, 750, 250);
	MoveToEx(hdc, 50, 280, NULL);

	MoveToEx(hdc, 100, 150, NULL);
	LineTo(hdc, 100, 270);

	MoveToEx(hdc, 166, 150, NULL);
	LineTo(hdc, 166, 270);

	MoveToEx(hdc, 233, 150, NULL);
	LineTo(hdc, 233, 270);

	MoveToEx(hdc, 298, 150, NULL);
	LineTo(hdc, 298, 270);

	MoveToEx(hdc, 365, 150, NULL);
	LineTo(hdc, 365, 270);

	MoveToEx(hdc, 430, 150, NULL);
	LineTo(hdc, 430, 270);

	MoveToEx(hdc, 497, 150, NULL);
	LineTo(hdc, 497, 270);

	MoveToEx(hdc, 562, 150, NULL);
	LineTo(hdc, 562, 270);

	MoveToEx(hdc, 628, 150, NULL);
	LineTo(hdc, 628, 270);

	MoveToEx(hdc, 700, 150, NULL);
	LineTo(hdc, 700, 270);

	currentPen = (HPEN)SelectObject(hdc, penFreeSeats);
	int k = 0;
	int startX = 110;
	for (size_t j = 0; j < 9; j++)
	{
		drawBox(startX + k, 175, hdc, false);
		k += 67;
	}
	k = 0;
	for (size_t j = 0; j < 9; j++)
	{
		drawBox(startX + k, 230, hdc, false);
		k += 67;
	}
	k = 0;
	size_t tmpBookedSeat;
	currentPen = (HPEN)SelectObject(hdc, penBookedSeats);
	for (size_t i = 0; i < bookedSeats.size(); i++)
	{
		tmpBookedSeat = bookedSeats[i];
		for (size_t j = 0; j < 9; j++)
		{
			if (tmpBookedSeat % 2 == 0 && tmpBookedSeat == (j + 1) * 2)
			{
				drawBox(startX + k, 230, hdc, true);
			}
			if (tmpBookedSeat % 2 == 1 && tmpBookedSeat == (j + 1) * 2 - 1)
			{
				drawBox(startX + k, 175, hdc, true);
			}

			k += 67;
		}
		k = 0;
	}

}
void CarView::handleLuxe(size_t &place, HDC hdc)
{
	place = 0;

	vector<size_t> bookedSeats = railCar.getBookedSeats();

	int x = 0;
	int oldX = x;
	int y = 0;
	int oldY = y;

	int numX = 1;
	int numY = 0;

	drawSelectedSeat(110, 175, hdc);
	int k = _getch();
	bool choose = false;
	size_t tmpBookedSeat;
	size_t index = 0;
	bool booked = false;
	while (!choose)
	{
		drawBox(110 + oldX, 175 + oldY, hdc, booked);
		booked = false;
		for (size_t i = 0; i < bookedSeats.size(); i++)
		{
			tmpBookedSeat = bookedSeats[i];
			if (numY == 1)
			{
				if (tmpBookedSeat == numX * 2)
				{
					booked = true;
					break;
				}
			}
			else if (numY == 0)
			{
				if (tmpBookedSeat == numX * 2 - 1)
				{
					booked = true;
					break;
				}
			}
		}

		oldX = x;
		oldY = y;
		drawSelectedSeat(110 + x, 175 + y, hdc);
		k = _getch();
		switch (k)
		{
		case KEY_RIGHT:
			if (x < 500)
			{
				x += 67;
				numX++;
			}
			break;
		case KEY_LEFT:
			if (x > 0)
			{
				x -= 67;
				numX--;
			}
			break;
		case KEY_DOWN:
			numY++;
			break;
		case KEY_UP:
			numY--;
			break;
		case KEY_ENTER:
			choose = true;
			if (numY == 0)
			{
				place = numX * 2 - 1;
			}
			else if (numY == 1)
			{
				place = numX * 2;
			}
		}

		if (numY == 0)
			y = 0;
		else if (numY == 1)
			y = 55;
		else if (numY == 2)
			numY = 1;
		else if (numY == -1)
			numY = 0;

		bool needToWrite = false;
		for (size_t i = 0; i < bookedSeats.size(); i++)
		{
			if (place == bookedSeats[i])
			{
				choose = false;
				needToWrite = true;
			}
		}
		if (needToWrite)
			printAtCenterOfLine(25, "This place is already booked. Choose another.", Printer(Color::High_intensity_white, Color::Blue));
	}
}
View * CarView::handle()
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN pen(CreatePen(PS_SOLID, 3, RGB(255, 255, 255)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	View* nextView = this;


	size_t place;
	switch (railCar.getType())
	{
	case RailCarType::ReservedSeat:
		handleReserved(place, hdc);
		break;
	case RailCarType::Compartment:
		handleCompartment(place, hdc);
		break;
	case RailCarType::Luxe:
		handleLuxe(place, hdc);
		break;
	}

	vector<size_t> bookedPlacesForOneUser = CustomerOrder::getPlaces();
	bookedPlacesForOneUser.push_back(place);
	CustomerOrder::setPlaces(bookedPlacesForOneUser);

	//here must be next (#5) view
	nextView = this;
	return nextView;
}

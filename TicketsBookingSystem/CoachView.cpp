#include "CoachView.h"
#include "ChoosePlaceView.h"
#include "DataHandler.h"
#include <conio.h>
#include "CustomerOrder.h"

CoachView::CoachView()
{
	DataHandler::loadTrain(inf);
}

HWND handlew = GetConsoleWindow();
//HDC dc = GetDC(handlew);

HPEN redPen = CreatePen(PS_SOLID, 3, RGB(151, 0, 0));
HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
HPEN bluePenSmaller = CreatePen(PS_SOLID, 2, RGB(0, 0, 128));
HPEN redPenSmaller = CreatePen(PS_SOLID, 2, RGB(151, 0, 0));
HPEN blackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

HBRUSH PenWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH PenBlue = CreateSolidBrush(RGB(0, 0, 128));
HBRUSH PenLightBlue = CreateSolidBrush(RGB(152, 188, 205));
HBRUSH PenDarkerWhite = CreateSolidBrush(RGB(140, 140, 140));
HBRUSH PenBlack = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH PenRed = CreateSolidBrush(RGB(151, 0, 0));


void drawSquare(int left, int top, bool chosen)
{
	SelectObject(dc, redPen);
	SelectObject(dc, chosen ? PenWhite : PenDarkerWhite);

	Rectangle(dc, left, top, left + 80, top + 40);
}

void drawChain(int left, int right)
{
	SelectObject(dc, redPen);
	SelectObject(dc, PenRed);

	Rectangle(dc, left, 219, right, 221);
}

void CoachView::drawTrains(size_t qntOfCars)
{
	int carNum = IsSelected + 1;
	int part = (carNum + (7 - carNum % 7)) / 7 - (carNum % 7 == 0 ? 1 : 0);

	SelectObject(dc, bluePen);
	SelectObject(dc, PenBlue);
	Rectangle(dc, 0, 200, 800, 240);

	size_t carsToDraw = (part * 7 > qntOfCars ? qntOfCars - (part - 1) * 7 : 7);
	for (int i = 0; i < carsToDraw; i++)
	{
		if (i == IsSelected % 7)
			drawSquare(60 + i * 100, 200, true);
		else
			drawSquare(60 + i * 100, 200, false);
	}
	for (int i = 0; i < carsToDraw + 1; i++)
	{
		if (part == 1 && i == 0);
		else if (part == qntOfCars / 7 + 1 && i == carsToDraw);
		else
			drawChain(40 + i * 100, 60 + i * 100);
	}
}

void CoachView::drawMenu(int x, int y, int x1, int y1)
{
	Printer printer(Color::High_intensity_white, Color::Blue);

	printAtCenterOfLine(3, "Train # ", printer);
	setCursor(50, 3);
	cout << inf.getNumber();
	printAtCenterOfLine(4, "Train Name: ", printer);
	setCursor(50, 4);
	cout << inf.getFullName();
	printAtCenterOfLine(5, "Departure time:", printer);
	setCursor(50, 5);
	cout << inf.getTimeOfDeparture();
	printAtCenterOfLine(6, "Arrival time:", printer);
	setCursor(50, 6);
	cout << inf.getTimeOfArrival();
	printAtCenterOfLine(9, "Select Coach:", printer);
	setCursor(50, 9);

	printAtCenterOfLine(18, "Coach # ", printer);
	printAtCenterOfLine(19, "Free places: ", printer);
	printAtCenterOfLine(20, "Type of Coach: ", printer);
	printAtCenterOfLine(21, "Price: ", printer);


	size_t CoachNumber = inf.getRailCars().size();

	vector<RailCarInformation> railCars = inf.getRailCars();
	RailCarType type = railCars[IsSelected].getType();
	double price = railCars[IsSelected].getTicketPrice();
	int freePlaces = railCars[IsSelected].getNumOfFreeSeats();
	string str;

	setCursor(50, 19);
	cout << freePlaces;

	setCursor(50, 21);
	cout << price << "  ";


	switch (type)
	{
	case RailCarType::ReservedSeat:
		{
			str = "Reserved Seat";
			setCursor(50, 20);
			cout << str << "       ";

			break;
		}

	case RailCarType::Compartment:
		{
			str = "Compartment";
			setCursor(50, 20);
			cout << str << "       ";

			break;
		}
	case RailCarType::Luxe:
		{
			str = "Luxe";
			setCursor(50, 20);
			cout << str << "       ";


			break;
		}
	}

	setCursor(50, 18);
	cout << IsSelected + 1 << "  ";

	Sleep(10);
	drawTrains(CoachNumber);

}

void CoachView::draw()
{
	drawMenu(60, 200, 140, 240);
}

View* CoachView::handle()
{
	View* newView = this;
	size_t CoachNumber = inf.getRailCars().size();
	char input = ' ';
	while (input != 13)
	{
		input = _getch();
		if (input == 13)
		{
			CustomerOrder::setRailCarNumber(IsSelected + 1);
			newView = new CarView();
			break;
		}
		switch (input)
		{
		case KEY_LEFT: IsSelected -= 1;
			break;
		case KEY_RIGHT: IsSelected += 1;
			break;
		}
		
		if (IsSelected == CoachNumber) IsSelected--;
		else if (IsSelected < 0) IsSelected++;

		drawMenu(60, 200, 140, 240);
	}

	return newView;
}

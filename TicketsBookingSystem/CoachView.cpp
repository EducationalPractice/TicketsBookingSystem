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
HDC dc = GetDC(handlew);

HPEN redPen = CreatePen(PS_SOLID, 3, RGB(151, 0, 0));
HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
HPEN bluePenSmaller = CreatePen(PS_SOLID, 2, RGB(0, 0, 128));
HPEN redPenSmaller = CreatePen(PS_SOLID, 2, RGB(151, 0, 0));
HPEN blackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

HBRUSH PenWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH PenBlue = CreateSolidBrush(RGB(90, 126, 143));
HBRUSH PenLightBlue = CreateSolidBrush(RGB(152, 188, 205));
HBRUSH PenDarkerWhite = CreateSolidBrush(RGB(243, 243, 243));
HBRUSH PenBlack = CreateSolidBrush(RGB(0, 0, 0));

void drawFrame(int x1, int y1, int x2, int y2)
{
	SelectObject(dc, redPen);
	SelectObject(dc, PenWhite);
	Rectangle(dc, x1, y1, x2, y2);
}
void deleteFrame(int x1, int y1, int x2, int y2)
{
	SelectObject(dc, redPen);
	SelectObject(dc, PenBlue);
	Rectangle(dc, x1, y1, x2, y2);
}

void drawSquare(int x1, int y1)
{
	SelectObject(dc, redPen);
	SelectObject(dc, redPen);

	for (int i = 0; i < 20; i++)
	{
		int position_x = x1 - 20 + i;
		MoveToEx(dc, position_x, y1 + 20, NULL);
		LineTo(dc, position_x, y1 + 20);
	}

	for (int i = 0; i < 80; i++)
	{
		int position_x = x1 + i;
		MoveToEx(dc, position_x, y1, NULL);
		LineTo(dc, position_x, y1);
	}
	for (int i = 0; i < 40; i++)
	{
		int position_y = y1 + i;
		MoveToEx(dc, x1, position_y, NULL);
		LineTo(dc, x1, position_y);
	}

	for (int i = 0; i < 80; i++)
	{
		int position_x = x1 + i;
		MoveToEx(dc, position_x, y1 + 40, NULL);
		LineTo(dc, position_x, y1 + 40);
	}
	for (int i = 0; i < 40; i++)
	{
		int position_y = y1 + i;
		MoveToEx(dc, x1 + 80, position_y, NULL);
		LineTo(dc, x1 + 80, position_y);
	}
}


void CoachView::drawMenu(int x,int y, int x1, int y1)
{
	Printer printer(Color::High_intensity_white, Color::Blue);

	printAtCenterOfLine(3, "Train # ", printer);
	setCursoreAtPosition(50, 3);
	cout << inf.getNumber();
	printAtCenterOfLine(4, "Train Name: ", printer);
	setCursoreAtPosition(50, 4);
	cout << inf.getFullName();
	printAtCenterOfLine(5, "Departure time:", printer);
	setCursoreAtPosition(50, 5);
	cout << inf.getTimeOfDeparture();
	printAtCenterOfLine(6, "Arrival time:", printer);
	setCursoreAtPosition(50, 6);
	cout << inf.getTimeOfArrival();
	printAtCenterOfLine(9, "Select Coach:", printer);
	setCursoreAtPosition(50, 9);

	printAtCenterOfLine(18, "Coach # ", printer);
	printAtCenterOfLine(19,"Free places: ", printer);
	printAtCenterOfLine(20, "Type of Coach: ", printer);
	printAtCenterOfLine(21, "Price: ", printer);
	
	
	size_t CoachNumber = inf.getRailCars().size();

	for (int i = 0; i < CoachNumber; i++)
	{

		drawSquare(60 + i * 100, 200);
	}
	vector<RailCarInformation> railCars = inf.getRailCars();
	RailCarType type1 = railCars[IsSelected].getType();
	double price = railCars[IsSelected].getTicketPrice();
	int freePlaces = railCars[IsSelected].getNumOfFreeSeats();
	string str;

	setCursoreAtPosition(50, 19);
	cout << freePlaces;

	setCursoreAtPosition(50, 21);
	cout << price;

	

	switch (type1)
	{
	case RailCarType::ReservedSeat:
	{
		str = "Reserved Seat";

		setCursoreAtPosition(50, 20);
		cout << str;
		
		break;
	}

	case RailCarType::Compartment:
	{
		str = "Compartment";
		setCursoreAtPosition(50, 20);
		cout << str;
	
		break;
	}
	case RailCarType::Luxe: {
		str = "Luxe";
		setCursoreAtPosition(50, 20);
		cout << str;
		

		break;
	}
}
	
	switch (IsSelected)
	{
	case 0:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected+1;
		

		 
		drawFrame(x, y, x1, y1);
		deleteFrame(x + 180, y, x1 + 20, y1);
		deleteFrame(x + 600, y, x1 + 600, y1);

	}         break;

	case 1:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected+1;

		
		drawFrame(x + 180, y, x1 + 20, y1);
		deleteFrame(x, y, x1, y1);
		deleteFrame(x + 200, y, x1 + 200, y1);
		break;
	}
	case 2:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected+1;

		
		drawFrame(x + 200, y, x1 + 200, y1);
		deleteFrame(x + 180, y, x1 + 20, y1);
		deleteFrame(x + 300, y, x1 + 300, y1);
		break;
	}
	case 3:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected + 1;

		
		drawFrame(x + 300, y, x1 + 300, y1);
		deleteFrame(x + 200, y, x1 + 200, y1);
		deleteFrame(x + 400, y, x1 + 400, y1);
		break;
	}
	case 4:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected+1;

		
		drawFrame(x + 400, y, x1 + 400, y1);
		deleteFrame(x + 300, y, x1 + 300, y1);
		deleteFrame(x + 500, y, x1 + 500, y1);
		break;
	}
	case 5:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected+1;

		
		drawFrame(x + 500, y, x1 + 500, y1);
		deleteFrame(x + 400, y, x1 + 400, y1);
		deleteFrame(x + 600, y, x1 + 600, y1);
		break;
	}
	case 6:
	{
		setCursoreAtPosition(50, 18);
		cout << IsSelected+1;

		
		drawFrame(x + 600, y, x1 + 600, y1);
		deleteFrame(x + 500, y, x1 + 500, y1);
		deleteFrame(x, y, x1, y1);
		break;
	}
	}
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
			CustomerOrder::setRailCarNumber(IsSelected+1);
			newView = new CarView();
			break;
		}
		switch (input)
		{
		case KEY_LEFT: IsSelected -= 1; break;
		case KEY_RIGHT: IsSelected += 1; break;
		}
		IsSelected = IsSelected % CoachNumber;
		if (IsSelected < 0) IsSelected += 1;
		drawMenu(60, 200, 140, 240);

	}
	
	return newView;
}
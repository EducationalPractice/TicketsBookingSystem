#include <iostream>
#include "Views.h"
#include "ConsoleFunctions.h"
#include "Colors.h"

int main() {
	showConsoleCursor(false);
	setConsoleToLucidaConsole();
	setConsoleSize(60, 30);
	View* view = new StartView();

	while (view != NULL)
	{
		View* newView;
		system("cls");
		system("Color 1F");
		view->draw();
		newView = view->handle();
		if (view != newView)
		{
			delete view;
			view = newView;
		}
	}
	return 0;
}
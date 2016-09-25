#include "Printer.h"
#include <iostream>
#include <windows.h>
using namespace std;
Printer::Printer(Color _colorOfText, Color _colorOfBackground) : colorOfText(_colorOfText), colorOfBackground(_colorOfBackground) {}

void Printer::print(string text)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ((int)colorOfText + (int)colorOfBackground * 16));
	cout << text;
}
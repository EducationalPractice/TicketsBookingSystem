#pragma once
#include <string>
#include "Colors.h"

using namespace std;

class Printer
{
private:
	Color colorOfText;
	Color colorOfBackground;
public:
	Printer();
	Printer(Color _colorOfText, Color _colorOfBackground);
	void print(string text);
};
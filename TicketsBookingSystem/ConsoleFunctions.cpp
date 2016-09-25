#include "ConsoleFunctions.h"
#include "Printer.h"
#include <windows.h>
#include <string>

using namespace std;

HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
int consoleWidth;
int consoleHeight;

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;

	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConOut, TRUE, &r);

	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConOut, c);
}

void setCursoreAtPosition(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConOut, pos);
}

void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}

void printAtCenterOfLine(int line, string text, Printer p)
{
	int textSize = text.size();
	int x_pos = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2;
	setCursoreAtPosition(x_pos, line);
	p.print(text);
}

void setConsoleToLucidaConsole()
{
	COORD dwFontSize;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return;

	dwFontSize.X = 10;
	dwFontSize.Y = 16;
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	info.dwFontSize = dwFontSize;
	SetCurrentConsoleFontEx(output, false, &info);
}
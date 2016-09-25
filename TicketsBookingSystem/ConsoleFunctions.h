#pragma once

#include <string>
#include <windows.h>
#include "Printer.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27
#define KEY_WHITESPACE 32

using namespace std;

extern HANDLE hConOut;
extern int consoleWidth;
extern int consoleHeight;

void setConsoleSize(int width, int height);
void setCursoreAtPosition(int x, int y);
void showConsoleCursor(bool showFlag);
void printAtCenterOfLine(int line, string text, Printer p);
void setConsoleToLucidaConsole();
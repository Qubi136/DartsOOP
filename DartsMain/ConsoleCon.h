#pragma once
#include <iostream>
#include <string.h>
#include <windows.h>
#include <conio.h>


using namespace std;

namespace console {

	void SetConsoleSize(int width, int height);
	void SetConsoleFont(int fontWidth, int fontHeight);
	void SetConsoleBufferSize(int columns, int rows);
	void DisableScrollAndResize();
	void SetingsForAnsii();


	void saveCursorPosition();
	void restoreCursorPosition();

	int actionIndicatorForMenu(int zero_line, int end_poz, int posinline = 1);

	void setCursorAbsolutePosition(int row, int col);
	void setCursorPositionInLine(int col);
	void setCursorPositionShiftUp(int row);
	void setCursorPositionShiftDown(int row);
	void setCursorPositionShiftRight(int offset);
	void setCursorPositionShiftLeft(int offset);
	void setCursorShiftUpOneLine();
	void clearOurAllLine();
	void clearConsoleScreen();
	void setConsoleTextColor(const char color[]);
	void setFoneColor(const char color[]);
	void resetConsoleColor();
	void moveCursorDown();
	void indicator_on(const char sumbol[] = "  ", int posinline = 1);
	void indicator_off(int posinline = 1);
}
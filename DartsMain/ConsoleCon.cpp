#include "ConsoleCon.h"




void console::SetConsoleSize(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); // Get the current console window size

	// Move and resize the console window
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void console::SetConsoleFont(int fontWidth, int fontHeight) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontWidth; // Width of each character in the font
	cfi.dwFontSize.Y = fontHeight; // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void console::SetConsoleBufferSize(int columns, int rows) {
	COORD coord;
	coord.X = columns;
	coord.Y = rows;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void console::DisableScrollAndResize() {
	// Get console window handle
	HWND console = GetConsoleWindow();

	// Get console screen buffer info
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	// Set the window size to the buffer size
	SMALL_RECT windowSize = { 0, 0, csbi.dwSize.X - 1, csbi.dwSize.Y - 1 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

	// Disable resizing
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);

	// Set the screen buffer size to the window size to disable scrollbars
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), csbi.dwSize);
}

void console::SetingsForAnsii() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hConsole, &mode);
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // Устанавливаем флаг для включения поддержки ANSI Escape-кодов
	SetConsoleMode(hConsole, mode);
}

void console::setCursorAbsolutePosition(int row, int col) {


	cout << "\033[" << row << ";" << col << "H";


}

void console::setCursorPositionInLine(int col) {


	cerr << "\033[" << col << "G";

}

void console::setCursorPositionShiftUp(int row) {

	cerr << "\033[" << row << "A";
}

void console::setCursorShiftUpOneLine() {

	cerr << "\033[A";
}

void console::clearOurAllLine()
{
	cerr << "\033[2K";
}

void console::setCursorPositionShiftDown(int row) {


	cerr << "\033[" << row << "B";
}

void console::setCursorPositionShiftRight(int offset) {
	cout << "\033[" << offset << "C";
}

void console::setCursorPositionShiftLeft(int offset) {
	cout << "\033[" << offset << "D";
}

void console::clearConsoleScreen() {
	cout << "\033[2J\033[1;1H";
	//system("cls");
}

void console::setConsoleTextColor(const char color[]) {

	if (color == "black") {
		cerr << "\033[30m";
	}
	else if (color == "red") {
		cerr << "\033[31m";
	}
	else if (color == "green") {
		cerr << "\033[32m";
	}
	else if (color == "yellow") {
		cerr << "\033[33m";
	}
	else if (color == "blue") {
		cerr << "\033[34m";
	}
	else if (color == "purple") {
		cerr << "\033[35m";
	}
	else if (color == "white") {
		cerr << "\033[37m";
	}
	else cerr << "nan undefind text color";
}

void console::setFoneColor(const char color[]) {

	if (color == "black") {
		cerr << "\033[40m";
	}
	else if (color == "red") {
		cerr << "\033[41m";
	}
	else if (color == "green") {
		cerr << "\033[42m";
	}
	else if (color == "yellow") {
		cerr << "\033[43m";
	}
	else if (color == "blue") {
		cerr << "\033[44m";
	}
	else if (color == "purple") {
		cerr << "\033[45m";
	}
	else if (color == "white") {
		cerr << "\033[47m";
	}
	else cerr << "nan undefind fone color";
}

void console::resetConsoleColor() {

	cerr << "\033[0m";
}

void console::moveCursorDown() {

	cerr << "\033[B";
}

void console::indicator_on(const char sumbol[], int posinline) {
	console::setCursorPositionInLine(posinline);
	console::setFoneColor("purple");
	cout << sumbol;
	console::setCursorPositionInLine(1);
	console::setFoneColor("black");
}

void console::indicator_off(int posinline) {
	console::setCursorPositionInLine(posinline);
	//setFoneColor("black");
	cout << " ";
	setCursorPositionInLine(1);
}

void console::saveCursorPosition() {
	cerr << ("\033[s"); // ANSI escape sequence для сохранения позиции курсора
}

void console::restoreCursorPosition() {
	cerr << ("\033[u"); // ANSI escape sequence для восстановления позиции курсора
}

int console::actionIndicatorForMenu(int zero_line, int end_poz, int posinline) {

	char ch; short num = 1;
	console::setCursorAbsolutePosition(zero_line, posinline);
	char sumb[] = ">";

	console::indicator_on(sumb, posinline);

	while (true) {
		ch = _getch();
		if (ch == 'P' && num < end_poz) {
			console::indicator_off(posinline);
			console::setCursorPositionShiftDown(1);
			num++;
			console::indicator_on(sumb, posinline);
		}
		else if (num > 1 && ch == 'H') {
			console::indicator_off(posinline);
			console::setCursorPositionShiftUp(1);
			num--;
			console::indicator_on(sumb, posinline);

		}
		else if (ch == '\r') {
			console::indicator_off();
			cerr << "\033[?25h";
			return num;
		}
	}
}

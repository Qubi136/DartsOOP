#include <iostream>
#include "defsetings.h"
#include "Game.h"

//const std::wstring str(L"Darts.exe");
const string menu1("Darts");
const string menu2("Press any key to continue");
const string mainMenu1("Start game");
const string gameStart1("Enter first player name: ");
const string gameStart2("Enter second player name: ");


int main()
{
    settings::mySetings(600, 400, 16, 18);
    cout << "\x1b[?25l";
    cout.flush();
    field(10, 10, menu1.length()).print(menu1);
    field(11, 10, menu2.length()).print(menu2);
    _getch();
    console::clearConsoleScreen();
    field(10, 10, mainMenu1.length()).print(mainMenu1);
    field(11, 10, mainMenu2.length()).print(mainMenu2);
    int choice = console::actionIndicatorForMenu(10, 2, 9);
    if (choice == 1) {
        console::clearConsoleScreen();
        string name1, name2;
        field(10, 0, gameStart1.length()).print(gameStart1);
        console::setCursorAbsolutePosition(10, gameStart1.length() + 1);
        cin >> name1;
        console::clearConsoleScreen();
        field(10, 0, gameStart2.length()).print(gameStart2);
        console::setCursorAbsolutePosition(10, gameStart2.length() + 1);
        cin >> name2;
        Game game(name1, name2);
        game.startGame();
    }
}


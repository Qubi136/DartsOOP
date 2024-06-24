#pragma once
#include "target.h"
#include "aim.h"
#include "ConsoleCon.h"
#include "mainapp.h"
#include "Field.h"
#include "Leg.h"

const string mainMenu2("Quit");
const string mainMenu3("Continue");
const string winGame("Restart game");
int choice;
Target targ(300, 300);

class Game {
    Leg leg;
    string player1Name;
    string player2Name;

public:
    Game(const string& p1, const string& p2)
        : player1Name(p1), player2Name(p2) {
        leg.setNames(player1Name, player2Name);
    }

    string whichTurn(int i) {
        if (i == 1) {
            return player1Name;
        }
        else if (i == 2) {
            return player2Name;
        }
    }

    void startGame() {
        MainConsoleApp mainApp;
        console::clearConsoleScreen();
        string st("----");
        Aim aim;
        cout << "\x1b[?25l";
        cout.flush();
        field(0, 0, player1Name.length()).print(player1Name);
        field(2, 0, leg.getCurrentScore(player1Name).length()).print(leg.getCurrentScore(player1Name));
        field(3, 0, leg.legWinsInString(player1Name).length()).print(leg.legWinsInString(player1Name));
        field(0, 20, player2Name.length()).print(player2Name);
        field(2, 20, leg.getCurrentScore(player2Name).length()).print(leg.getCurrentScore(player2Name));
        field(3, 20, leg.legWinsInString(player2Name).length()).print(leg.legWinsInString(player2Name));

        while (true) {
            int i = 1;
            while (i <= 2) {
                int j = 1;
                    while (j <= 3) {
                        string str = "Turn of ";
                        field(7, 10, str.length()).print(str);
                        field(7, str.length()+10, whichTurn(i).length()).print(whichTurn(i));
                        st[0] = _getch();
                        if (st[0] == 27) {
                            console::clearConsoleScreen();
                            cout << "\x1b[?25l";
                            cout.flush();
                            field(10, 10, mainMenu3.length()).print(mainMenu3);
                            field(11, 10, mainMenu2.length()).print(mainMenu2);
                            choice = console::actionIndicatorForMenu(10, 2, 9);
                            if (choice == 2) {
                                return;
                            }
                            else
                                console::clearConsoleScreen();
                        }
                        mainApp.sendMessageToErrorConsole(st);
                        if (st[0] == 'e') {
                            string str = "Throw Dart at ";
                            field(7 + j, 10, str.length()).print(str);
                            console::setCursorAbsolutePosition(7+j, str.length()+10);
                            j++;
                        }
                        aim.aimControl(st, targ);
                        if (st[0] == 'e') {
                            int score = leg.calcScore(whichTurn(i), aim.scoreToGame(targ), aim.isWin(targ));
                            cout << " " << score;
                            if (score <= 1 && score != 0)
                            {
                                j = 4;
                                break;
                            }
                            else if (score == 0 && aim.isWin(targ))
                            {
                                leg.setLegWins(whichTurn(i));
                                break;
                            }
                        }                        
                        cout << "\x1b[?25l";
                        cout.flush();
                    }
                    leg.changeCurrentScore();
                    console::clearConsoleScreen();
                    field(0, 0, player1Name.length()).print(player1Name);
                    field(2, 0, leg.getCurrentScore(player1Name).length()).print(leg.getCurrentScore(player1Name));
                    field(3, 0, leg.legWinsInString(player1Name).length()).print(leg.legWinsInString(player1Name));
                    field(0, 20, player2Name.length()).print(player2Name);
                    field(2, 20, leg.getCurrentScore(player2Name).length()).print(leg.getCurrentScore(player2Name));
                    field(3, 20, leg.legWinsInString(player2Name).length()).print(leg.legWinsInString(player2Name));
                    if (leg.legWinsInInt(whichTurn(i)) == 3) {
                        console::clearConsoleScreen();
                        cout << "\x1b[?25l";
                        cout.flush();
                        string str = (whichTurn(i)) + " Wins";
                        field(10, 10, str.length()).print(str);
                        field(11, 10, winGame.length()).print(winGame);
                        field(12, 10, mainMenu3.length()).print(mainMenu2);
                        choice = console::actionIndicatorForMenu(11, 2, 9);
                        if (choice == 2) {
                            return;
                        }
                        else {
                            console::clearConsoleScreen();
                            leg.resetScores();
                            field(0, 0, player1Name.length()).print(player1Name);
                            field(2, 0, leg.getCurrentScore(player1Name).length()).print(leg.getCurrentScore(player1Name));
                            field(3, 0, leg.legWinsInString(player1Name).length()).print(leg.legWinsInString(player1Name));
                            field(0, 20, player2Name.length()).print(player2Name);
                            field(2, 20, leg.getCurrentScore(player2Name).length()).print(leg.getCurrentScore(player2Name));
                            field(3, 20, leg.legWinsInString(player2Name).length()).print(leg.legWinsInString(player2Name));
                        }
                    }
                    i++;

            }
        }
    }
};
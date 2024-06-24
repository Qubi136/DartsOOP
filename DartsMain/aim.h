#pragma once
#include <conio.h>
#include "target.h"

const int Arrow_Up = 72;
const int Arrow_Down = 80;
const int Arrow_Left = 75;
const int Arrow_Right = 77;
const int Escape_but = 27;
const int Enter = 13;

class Aim {
    int x = 151;
    int y = 151;
    vector<pair<int, int>> scopeCoord = {
            {y, x}, {y + 1, x},
            {y - 1, x}, {y, x + 1},
            {y, x - 1}
    };
    bool isScopeInCircle(int dx, int dy, Target& targ) {
        bool check = true;
        for (int i = 0; i < 5; i++) {
            if (!targ.isInCircle(scopeCoord[i].second + dx - 1, scopeCoord[i].first + dy - 1, 150)) {
                check = false;
                break;
            }
        }
        return check;
    }

    void scopeChange() {
        scopeCoord[0] = { y, x };
        scopeCoord[1] = { y + 1, x };
        scopeCoord[2] = { y - 1, x };
        scopeCoord[3] = { y, x + 1 };
        scopeCoord[4] = { y, x - 1 };
    }
public:
    Aim() {
    }

    int scoreToGame(Target& targ) {
        return targ.getScore(scopeCoord[0].second - 1, scopeCoord[0].first - 1);
    }
    void aimControl(string str, Target& targ) {
        {
            char ch = str[0];
                    switch (ch) {
                    case 'w':
                        if (isScopeInCircle(0, -1, targ)) {
                            --y;
                            scopeChange();
                        }
                        break;
                    case 's':
                        if (isScopeInCircle(0, 1, targ)) {
                            ++y;
                            scopeChange();
                        }
                        break;
                    case 'a':
                        if (isScopeInCircle(-1, 0, targ)) {
                            --x;
                            scopeChange();
                        }
                        break;
                    case 'd':
                        if (isScopeInCircle(1, 0, targ)) {
                            ++x;
                            scopeChange();
                        }
                        break;
                    case 'e':
                        cout << targ.getScore(scopeCoord[0].second - 1, scopeCoord[0].first - 1);
                        break;
                    case 'r':
                        x = 151;
                        y = 151;
                        scopeChange();
                        break;
                    }
                }
            }
    bool isWin(Target& targ) {
        if (targ.isDouble(scopeCoord[0].second - 1, scopeCoord[0].first - 1, 150) || targ.isDoubleBull(scopeCoord[0].second - 1, scopeCoord[0].first - 1, 150)) {
            return true;
        }
        else return false;
    }
};
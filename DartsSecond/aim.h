#pragma once
#include <conio.h>
#include "target.h"

const int Arrow_Up = 72;
const int Arrow_Down = 80;
const int Arrow_Left = 75;
const int Arrow_Right = 77;
const int Escape_but = 27;
const int Enter = 13;
char buffer[1024];
HANDLE hPipe;
LPCWSTR pipeName = TEXT("\\\\.\\pipe\\MyPipe");
DWORD bytesRead;

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
        console::setFoneColor("purple");
        for (int i = 0; i < 5; i++) {
            console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
            std::cout << ' ';
        }
    }
     
    void aimControl(Target& targ) {
        {
            while (true) {
                if (ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL) != FALSE) {
                    buffer[bytesRead] = '\0';
                    char ch = buffer[0];
                    switch (ch) {
                    case 'w':
                        if (isScopeInCircle(0, -1, targ)) {
                            targ.targetChange(scopeCoord);
                            --y;
                            scopeChange();
                            for (int i = 0; i < 5; i++) {
                                console::setFoneColor("purple");
                                console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
                                std::cout << ' ';
                                console::setFoneColor("black");
                            }
                        }
                        break;
                    case 's':
                        if (isScopeInCircle(0, 1, targ)) {
                            targ.targetChange(scopeCoord);
                            ++y;
                            scopeChange();
                            for (int i = 0; i < 5; i++) {
                                console::setFoneColor("purple");
                                console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
                                std::cout << ' ';
                                console::setFoneColor("black");
                            }
                        }
                        break;
                    case 'a':
                        if (isScopeInCircle(-1, 0, targ)) {
                            targ.targetChange(scopeCoord);
                            --x;
                            scopeChange();
                            for (int i = 0; i < 5; i++) {
                                console::setFoneColor("purple");
                                console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
                                std::cout << ' ';
                                console::setFoneColor("black");
                            }
                        }
                        break;
                    case 'd':
                        if (isScopeInCircle(1, 0, targ)) {
                            targ.targetChange(scopeCoord);
                            ++x;
                            scopeChange();
                            for (int i = 0; i < 5; i++) {
                                console::setFoneColor("purple");
                                console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
                                std::cout << ' ';
                                console::setFoneColor("black");
                            }
                        }
                        break;
                    case 'r':
                        targ.targetChange(scopeCoord);
                        x = 151;
                        y = 151;
                        scopeChange();
                        for (int i = 0; i < 5; i++) {
                            console::setFoneColor("purple");
                            console::setCursorAbsolutePosition(scopeCoord[i].first, scopeCoord[i].second);
                            std::cout << ' ';
                            console::setFoneColor("black");
                        }
                        break;
                    }
                }
            }
        }
    }
};
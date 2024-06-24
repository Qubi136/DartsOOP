#pragma once
#include "ConsoleCon.h"
#include <string>


class field
{
public:
    field(int x, int y, int length);


    void print(const std::string& str, int startpos = 0) {
        console::saveCursorPosition();
        console::setCursorAbsolutePosition(x, y);

        int strLength = str.length();

        for (int i = startpos; i < this->length; ++i) {
            if (i < strLength) {
                std::cout << str[i];
            }
            else {
                std::cout << ' ';
            }
        }
        console::restoreCursorPosition();
    }


    void erase() {
        console::saveCursorPosition();
        console::setCursorAbsolutePosition(x, y);
        for (int i = 0; i < this->length; ++i) {
            std::cout << ' ';
        }
        console::restoreCursorPosition();
    }

private:

    int x = 0;
    int y = 0;
    int length;

};

field::field(int x, int y, int length) {
    this->x = x;
    this->y = y;
    this->length = length;
}

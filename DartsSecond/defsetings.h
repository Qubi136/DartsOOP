#pragma once
#include "ConsoleCon.h"
namespace settings {
    void mySetings(int a, int b, int c, int d) {
        console::clearConsoleScreen();
        console::SetingsForAnsii();
        console::SetConsoleFont(c, d);
        console::SetConsoleBufferSize(400, 400);
        console::SetConsoleSize(a, b);
        console::DisableScrollAndResize();
        srand(time(NULL));
    }
}
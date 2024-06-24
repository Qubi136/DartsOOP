#include <iostream>
#include "ConsoleCon.h"
#include "defsetings.h"
#include "target.h"
#include "game.h"
#include "mainapp.h"
#include "secondapp.h"
#include <thread>

int main() {
        settings::mySetings(800, 800, 2, 2);
        Game game;
        cout << "\x1b[?25l";
        cout.flush();
        game.startGame();

}

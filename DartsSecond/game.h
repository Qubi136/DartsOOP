#pragma once
#include "target.h"
#include "aim.h"

class Game {
public:
	Game() {
        AllocConsole();
        SetConsoleTitle(TEXT("Inform Console"));

        std::cout << "Outpat console" << std::endl;

        hPipe = CreateFile(pipeName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "pipe error" << std::endl;
        }
    
	}
    ~Game() {
        CloseHandle(hPipe);
        FreeConsole();
    }
	void startGame(){
        Target targ(300, 300);
		console::clearConsoleScreen();

		targ.print();
        Aim scope;
        scope.aimControl(targ);
	}
};
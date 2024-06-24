#include <iostream>
#include <windows.h>
#include <string>

#include <iostream>
#include <windows.h>
#include <string>

class ErrorConsoleApp {
public:
    ErrorConsoleApp() {
        // Создаем консоль для приложения-клиента
        AllocConsole();
        SetConsoleTitle(TEXT("Error Console"));
        std::cout << "outout app" << std::endl;

        // Открываем именованный канал для чтения данных
        hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\MyPipe"), PIPE_ACCESS_INBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, 1, 0, 0, 0, NULL);
        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "pipe error" << std::endl;
            return;
        }

        // Ожидаем подключения клиента к каналу
        std::cout << "conection to main app..." << std::endl;

        ConnectNamedPipe(hPipe, NULL);
    }

    ~ErrorConsoleApp() {
        // Закрываем консоль и канал
        CloseHandle(hPipe);
        FreeConsole();
    }

    // Чтение сообщений из именованного канала
    void readMessages() {
        DWORD bytesRead;
        char buffer[1024];

        while (true) {
            if (ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL) != FALSE) {
                buffer[bytesRead] = '\0'; // Добавляем завершающий нулевой символ
                std::cout << "get from main console: " << buffer << std::endl;
            }
        }
    }

private:
    HANDLE hPipe;


};
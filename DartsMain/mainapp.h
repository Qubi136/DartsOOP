#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <locale>
#include <codecvt>

std::string wstringToString(const std::wstring& wstr) {
    // Использование wstring_convert для преобразования
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    return convert.to_bytes(wstr);
}

class MainConsoleApp {
public:
    MainConsoleApp(const std::wstring& filePath = L"Darts.exe") {
        this->str = filePath;
        // Создаем консоль для основного приложения
        AllocConsole();
        SetConsoleTitle(TEXT("Main Console"));
        std::cout << "Main console created" << std::endl;

        // Открываем именованный канал для записи данных
        pipeName = L"\\\\.\\pipe\\MyPipe";
        hPipe = CreateNamedPipe(
            pipeName,                            // Имя канала
            PIPE_ACCESS_OUTBOUND,                // Режим доступа для записи
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // Тип и режим канала
            1,                                   // Количество экземпляров канала
            0, 0, 0, NULL);                      // Дополнительные параметры

        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Pipe creation error: " << GetLastError() << std::endl;
            return;
        }


        std::cout << "Waiting for client connection to the pipe..." << std::endl;
        if (!openExecutable(filePath)) {
            std::cerr << "Failed to open executable: " << GetLastError() << std::endl;
            return;
        }

        // Ожидаем подключения клиента к каналу
        ConnectNamedPipe(hPipe, NULL);

        // Устанавливаем основное окно в качестве активного
        SetForegroundWindow(mainWindow);
    }

    ~MainConsoleApp() {
        // Закрываем консоль
        FreeConsole();

        // Закрываем канал
        if (hPipe != INVALID_HANDLE_VALUE) {
            CloseHandle(hPipe);
        }
        std::string command = "taskkill /IM  Darts.exe /F";

        // Выполнение команды
        int result = system(command.c_str());

    }

    // Отправка сообщения в консоль для ошибок
    void sendMessageToErrorConsole(const std::string& message) {
        if (hPipe != INVALID_HANDLE_VALUE) {
            DWORD bytesWritten;
            WriteFile(hPipe, message.c_str(), message.length(), &bytesWritten, NULL);
        }
        else {
            std::cerr << "Failed to send message: pipe not open" << std::endl;
        }
    }

private:
    HANDLE hPipe;
    LPCWSTR pipeName;
    HWND mainWindow = GetConsoleWindow();
    std::wstring str;

    bool openExecutable(const std::wstring& filePath) {
        // Запускаем исполняемый файл
        HINSTANCE result = ShellExecute(NULL, L"open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);

        // Проверяем результат выполнения ShellExecute
        if ((int)result <= 32) {
            std::cerr << "Failed to open file: " << (int)result << std::endl;
            return false;
        }

        // Устанавливаем основное окно в качестве активного
        SetForegroundWindow(mainWindow);

        return true;
    }
};
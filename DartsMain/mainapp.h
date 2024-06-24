#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <locale>
#include <codecvt>

std::string wstringToString(const std::wstring& wstr) {
    // ������������� wstring_convert ��� ��������������
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> convert;
    return convert.to_bytes(wstr);
}

class MainConsoleApp {
public:
    MainConsoleApp(const std::wstring& filePath = L"Darts.exe") {
        this->str = filePath;
        // ������� ������� ��� ��������� ����������
        AllocConsole();
        SetConsoleTitle(TEXT("Main Console"));
        std::cout << "Main console created" << std::endl;

        // ��������� ����������� ����� ��� ������ ������
        pipeName = L"\\\\.\\pipe\\MyPipe";
        hPipe = CreateNamedPipe(
            pipeName,                            // ��� ������
            PIPE_ACCESS_OUTBOUND,                // ����� ������� ��� ������
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // ��� � ����� ������
            1,                                   // ���������� ����������� ������
            0, 0, 0, NULL);                      // �������������� ���������

        if (hPipe == INVALID_HANDLE_VALUE) {
            std::cerr << "Pipe creation error: " << GetLastError() << std::endl;
            return;
        }


        std::cout << "Waiting for client connection to the pipe..." << std::endl;
        if (!openExecutable(filePath)) {
            std::cerr << "Failed to open executable: " << GetLastError() << std::endl;
            return;
        }

        // ������� ����������� ������� � ������
        ConnectNamedPipe(hPipe, NULL);

        // ������������� �������� ���� � �������� ���������
        SetForegroundWindow(mainWindow);
    }

    ~MainConsoleApp() {
        // ��������� �������
        FreeConsole();

        // ��������� �����
        if (hPipe != INVALID_HANDLE_VALUE) {
            CloseHandle(hPipe);
        }
        std::string command = "taskkill /IM  Darts.exe /F";

        // ���������� �������
        int result = system(command.c_str());

    }

    // �������� ��������� � ������� ��� ������
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
        // ��������� ����������� ����
        HINSTANCE result = ShellExecute(NULL, L"open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);

        // ��������� ��������� ���������� ShellExecute
        if ((int)result <= 32) {
            std::cerr << "Failed to open file: " << (int)result << std::endl;
            return false;
        }

        // ������������� �������� ���� � �������� ���������
        SetForegroundWindow(mainWindow);

        return true;
    }
};
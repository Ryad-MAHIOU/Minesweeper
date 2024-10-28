#include "ConsoleManager.h";
#include <iostream>;
#include <windows.h>;
#include <conio.h>;
#include <string>;

int GetEntrance()
{
    int entrance = _getch();
    return entrance;
}

void FullScreen()
{
    HWND Hwnd = GetForegroundWindow();
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    LONG winstyle = GetWindowLong(Hwnd, GWL_STYLE);
    SetWindowLong(Hwnd, GWL_STYLE, (winstyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
    SetWindowPos(Hwnd, HWND_TOP, 0, 0, x, y, 0);
}

void MoveCursor(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(hConsole, coord);
}

void HideCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ClearScreen(int x, int y, int l, int h)
{
    std::cout << "\033[40m";
    std::string clear(l, ' ');
    for (int i = 0; i < h; i++)
    {
        MoveCursor(x, y + i);
        std::cout << clear << std::endl;
    }
}

int GetHeightConsole()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Hauteur
}

int GetLengthConsole()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1; // Largeur
}

void GetPosGrid(Data& data)
{
    data.gridPosX = (data.lengthConsole - data.length * 4) / 2;
    data.gridPosY = (data.heightConsole - data.height * 2) / 2;
}
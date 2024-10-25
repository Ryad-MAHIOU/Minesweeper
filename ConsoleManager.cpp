#pragma once
#include <iostream>;
#include <windows.h>;
#include <conio.h>;

int GetEntrance()
{
    int entrance = _getch();
    return entrance;
}

void fullsc()
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
    std::cout << "\033[40m\033[30m";
    MoveCursor(0, 0);
    for (int i = 0; i < h; i++)
        std::cout << ' ' * l << std::endl;
    MoveCursor(0, 0);
}
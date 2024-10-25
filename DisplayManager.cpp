#pragma once
#include "Data.h";
#include "ConsoleManager.cpp";
#include <iostream>;

#define BG_CONSOLE "\033[40m"
#define BG_FLAG "\033[100m"
#define GRAY "\033[90m"
#define BLACK "\033[30m"
#define RED "\033[31m"

#define MOTIF1 (char)(-60) // ─
#define MOTIF2 (char)(-77) // │

using namespace std;

void Print(char motif, int nb)
{
    for (int i = 0; i < nb; i++)
        cout << motif;
}

// Game screen
bool IsConnect(Data& data, int y, int x)
{
    if (data.matrix[y][x].isFlag)
        return true;
    else if (data.matrix[y][x].isDug || data.matrix[y][x].isFlag)
    {
        if (data.matrix[y][x].isMine)
            return false;
        else
            return true;
    }
    return false;
}

const char* GetColor(Data& data, int y, int x)
{
    if (data.matrix[y][x].isDug)
        return BG_CONSOLE;
    else
        return data.backgrounds[data.color];
}

void Display(Data& data)
{
    return;
}

void Loose(Data& data)
{
    for (int y = 0; y < data.height; y++)
    {
        for (int x = 0; x < data.length; x++)
        {
            if (data.matrix[y][x].isMine)
                data.matrix[y][x].isDug = true;
        }
    }
    Display(data);
    cout << RED << "  YOU LOST " << GRAY;
}

void Win(Data& data)
{
    for (int y = 0; y < data.height; y++)
    {
        for (int x = 0; x < data.length; x++)
        {
            if (data.matrix[y][x].isMine)
                data.matrix[y][x].isFlag = true;
        }
    }
    Display(data);
    cout << RED << "  YOU WON :)" << GRAY;
}

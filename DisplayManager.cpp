#include "DisplayManager.h";

#include <iostream>;

#define BG_CONSOLE "\033[40m"
#define BG_FLAG "\033[100m"
#define GRAY "\033[90m"
#define BLACK "\033[30m"
#define RED "\033[31m"

#define MOTIF1 (char)(-77) // │
#define MOTIF2 (char)(-60) // ─

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

void DisplayLine1(Data& data, int x, int y)
{
    MoveCursor(x, y);
    for (int x = 0; x < data.length - 1; x++)
        cout << "   " << MOTIF1;
    cout << "   ";
}

void DisplayLine2(Data& data, int x, int y)
{
    MoveCursor(x, y);
    for (int x = 0; x < data.length - 1; x++)
        cout << MOTIF2 << MOTIF2 << MOTIF2 << " ";
    cout << MOTIF2 << MOTIF2 << MOTIF2;
}

void Display(Data& data)
{
    ClearScreen(0, 0, data.lengthConsole, data.heightConsole);
    while (data.heightConsole < data.height * 2 || data.lengthConsole < data.length * 4)
    {
        int heightConsole = GetHeightConsole();
        int lengthConsole = GetLengthConsole();
        if (data.heightConsole != heightConsole || data.lengthConsole != lengthConsole)
        {
            data.heightConsole = heightConsole;
            data.lengthConsole = lengthConsole;
            ClearScreen(0, 0, data.lengthConsole, data.heightConsole);
        }
        MoveCursor(0, 0);
        cout << GRAY << "de-zoom";
    }
    ClearScreen(0, 0, 7, 1);
    cout << data.backgrounds[data.color];
    for (int y = 0; y < (data.height - 1) * 2; y += 2)
    {
        DisplayLine1(data, data.gridPosX, data.gridPosY + y);
        DisplayLine2(data, data.gridPosX, data.gridPosY + y + 1);
    }
    DisplayLine1(data, data.gridPosX, data.gridPosY + (data.height - 1) * 2);
}

void UpdatePlayer(Data& data)
{
    MoveCursor(data.gridPosX + data.lastPosX * 4, data.gridPosY + data.lastPosY * 2);
    cout << "d";
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

#pragma once
#include "UI.h";

#include <iostream>;
#include <conio.h>
#include <string>

#define GRAY "\033[90m"

using namespace std;

int GetLength(const char* str)
{
    int i = 0;
    for (i; str[i] != '\0'; i++);
    return i;
}

void DisplayButton(const char* str, const char* foreground, int x, int y, int l)
{
    int length = GetLength(str);
    string motif(l - 2, (char)(-60));
    // Première ligne
    MoveCursor(x, y);
    cout << foreground << (char)(-38) << motif << (char)(-65);
    // Deuxième ligne
    MoveCursor(x, y + 1);
    cout << (char)(-77);
    MoveCursor(x + (l - length) / 2, y + 1);
    cout << str;
    MoveCursor(x + l - 1, y + 1);
    cout << (char)(-77);
    // Troisième ligne
    MoveCursor(x, y + 2);
    cout << foreground << (char)(-64) << motif << (char)(-39);
}

bool DisplayUI(Data& data, int* option, const char** buttonsName, int buttonsNb, int l, const char* txt)
{
    int heightConsole = GetHeightConsole();
    int lengthConsole = GetLengthConsole();
    if (data.heightConsole != heightConsole || data.lengthConsole != lengthConsole)
    {
        data.heightConsole = heightConsole;
        data.lengthConsole = lengthConsole;
        ClearScreen(0, 0, data.lengthConsole, data.heightConsole);
    }
    int lengthTxt = GetLength(txt);
    if (data.heightConsole < buttonsNb * 3 + 1 || data.lengthConsole < l || data.lengthConsole < lengthTxt)
    {
        MoveCursor(0, 0);
        cout << GRAY << "de-zoom";
    }
    else
    {
        int x = (data.lengthConsole - l) / 2;
        int y = ((data.heightConsole - buttonsNb * 3) / 2) + 1;
        int i = 0;
        for (i; i < *option; i++)
            DisplayButton(buttonsName[i], GRAY, x, y + 3 * i, l);
        DisplayButton(buttonsName[*option], data.foregrounds[data.color], x, y + 3 * i, l);
        i++;
        for (i; i < buttonsNb; i++)
            DisplayButton(buttonsName[i], GRAY, x, y + 3 * i, l);
        if (txt == "Keys")
        {
            for (i = 0; i < buttonsNb - 1; i++)
            {
                MoveCursor(x, y + 3 * i + 1);
                cout << GRAY << "-> " << static_cast<char>(data.entrances[i]);
            }
        }
        MoveCursor((data.lengthConsole - lengthTxt) / 2, y - 1);
        cout << GRAY << txt;
        int entrance = GetEntrance();
        if (entrance == data.entrances[0])
        {
            if (*option == 0)
                *option = buttonsNb - 1;
            else
                *option = ((*option) - 1) % buttonsNb;
        }
        else if (entrance == data.entrances[1])
            *option = ((*option) + 1) % buttonsNb;
        else if (entrance == data.entrances[4] || entrance == 13)
            return false;
        return true;
    }
}

void Difficulty(Data& data)
{
    int option = 0;
    int* pOption = &option;
    const char* buttonsName[] = { "easy", "medium", "hard" };
    int buttonsNb = 3;
    int lengthButton = 12;
    bool difficulty = true;
    while (difficulty)
        difficulty = DisplayUI(data, pOption, buttonsName, buttonsNb, lengthButton, "Difficulty");
    switch (option)
    {
    case 0:
        data.height = 9;
        data.length = 9;
        break;
    case 1:
        data.height = 16;
        data.length = 16;
        break;
    case 2:
        data.height = 16;
        data.length = 30;
        break;
    }
}

bool DisplayRestart(Data& data, int* option)
{
    int x = 0;
    int y = 0;
    if (*option == 0)
    {
        DisplayButton("retry", data.foregrounds[data.color], x, y - 1, 15);
        DisplayButton("quit", GRAY, x + 17, y - 1, 15);
    }
    else
    {
        DisplayButton("retry", GRAY, x, y - 1, 15);
        DisplayButton("quit", data.foregrounds[data.color], x + 17, y - 1, 15);
    }
    MoveCursor(x, y);
    int entrance = GetEntrance();
    if (entrance == data.entrances[2] || entrance == data.entrances[3])
        *option = ((*option) + 1) % 2;
    else if (entrance == data.entrances[4] || entrance == 13)
        return false;
    return true;
}

// Pause screens

void Keys(Data& data)
{
    bool stay = true;
    int option = 0;
    int* pOption = &option;
    const char* buttonsName[] = { "up", "down", "left", "rigth", "A", "B", "return" };
    int buttonsNb = 7;
    while (stay)
    {
        bool keys = true;
        while (keys)
            keys = DisplayUI(data, pOption, buttonsName, buttonsNb, 20, "Keys");
        if (option == 6)
            stay = false;
        else
        {
            int newKey = _getch();
            data.entrances[option] = newKey;
        }
    }
}

void Themes(Data& data)
{
    bool stay = true;
    int option = 0;
    int* pOption = &option;
    const char* buttonsName[] = { "cyan", "magenta", "green", "yellow", "return" };
    int buttonsNb = 5;
    while (stay)
    {
        bool themes = true;
        while (themes)
            themes = DisplayUI(data, pOption, buttonsName, buttonsNb, 15, "Themes");
        if (option == 4)
            stay = false;
        else
            data.color = option;
    }
}

void Settings(Data& data)
{
    bool stay = true;
    int option = 0;
    int* pOption = &option;
    const char* buttonsName[] = { "keys", "themes", "return" };
    int buttonsNb = 3;
    while (stay)
    {
        bool settings = true;
        while (settings)
            settings = DisplayUI(data, pOption, buttonsName, buttonsNb, 15, "Settings");
        switch (option)
        {
        case 0:
            Keys(data);
            break;
        case 1:
            Themes(data);
            break;
        case 2:
            stay = false;
            break;
        }
    }
}

void Pause(Data& data)
{
    bool stay = true;
    int option = 0;
    int* pOption = &option;
    const char* buttonsName[] = { "resume", "settings", "quit" };
    int buttonsNb = 3;
    while (stay)
    {
        bool pause = true;
        while (pause)
            pause = DisplayUI(data, pOption, buttonsName, buttonsNb, 15, "Pause");
        switch (option)
        {
        case 0:
            stay = false;
            break;
        case 1:
            Settings(data);
            break;
        case 2:
            exit(0);
        }
    }
}
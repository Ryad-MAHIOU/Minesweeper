#pragma once
#include "Data.h";
#include "DisplayManager.cpp"
#include "Cell.cpp"
#include "CellsToUpdate.cpp"
#include "UI.cpp"
#include <iostream>;

void GetMine(Data& data)
{
    Cell** cpyMatrix = (Cell**)malloc(sizeof(Cell*) * data.height * data.length);
    int size = 0;
    for (int y2 = 0; y2 < data.height; y2++)
    {
        for (int x2 = 0; x2 < data.length; x2++)
        {
            if (data.posY - 1 <= y2 && y2 <= data.posY + 1 && data.posX - 1 <= x2 && x2 <= data.posX + 1)
                continue;
            cpyMatrix[size] = &(data.matrix[y2][x2]);
            size++;
        }
    }
    int nbMine = (data.height * data.length * 15) / 100;
    for (int i = 0; i < nbMine; i++)
    {
        int randNb = rand() % size;
        cpyMatrix[randNb]->isMine = true;
        memcpy(cpyMatrix[randNb], cpyMatrix[randNb] + 1, sizeof(int) * size - randNb - 0);
        size--;
    }
    free(cpyMatrix);
}

void GetNeightboor(Data& data, int y1, int x1)
{
    for (int y2 = y1 - 1; y2 <= y1 + 1; y2++)
    {
        for (int x2 = x1 - 1; x2 <= x1 + 1; x2++)
        {
            if (y2 == y1 && x2 == x1)
                continue;
            else if (y2 < 0 || x2 < 0)
                continue;
            else if (y2 >= data.height || x2 >= data.length)
                continue;
            if (data.matrix[y2][x2].isMine)
                data.matrix[y1][x1].nbMineAdjacent++;
        }
    }
}

void PutFlag(Data& data, int y, int x)
{
    if (data.matrix[y][x].isFlag == false && data.matrix[y][x].isDug == false)
        data.matrix[y][x].isFlag = true;
    else
        data.matrix[y][x].isFlag = false;
}

bool Dig(Data& data, int y1, int x1, bool bigDig)
{
    if (data.matrix[y1][x1].isFlag == false and data.matrix[y1][x1].isDug == false)
    {
        data.matrix[y1][x1].isDug = true;
        (data.nbCaseDug)++;
        if (data.matrix[y1][x1].isMine)
            return true;
        else if (data.matrix[y1][x1].nbMineAdjacent == 0)
        {
            for (int y2 = y1 - 1; y2 <= y1 + 1; y2++)
            {
                for (int x2 = x1 - 1; x2 <= x1 + 1; x2++)
                {
                    if (0 <= y2 && y2 < data.height && 0 <= x2 && x2 < data.length)
                    {
                        if (data.matrix[y2][x2].nbMineAdjacent == 0 && data.matrix[y2][x2].isDug == false && (y1 != y2 && x1 != x2))
                            Dig(data, y2, x2, false);
                        else if (data.matrix[y2][x2].isDug == false)
                            Dig(data, y2, x2, false);
                    }
                }
            }
        }
    }
    else if (data.matrix[y1][x1].isDug == true && bigDig)
    {
        int nbFlag = 0;
        for (int y2 = y1 - 1; y2 <= y1 + 1; y2++)
        {
            for (int x2 = x1 - 1; x2 <= x1 + 1; x2++)
            {
                if (0 <= y2 && y2 < data.height && 0 <= x2 && x2 < data.length)
                {
                    if (data.matrix[y2][x2].isFlag)
                        nbFlag++;
                }
            }
        }
        if (nbFlag == data.matrix[y1][x1].nbMineAdjacent)
        {
            for (int y2 = y1 - 1; y2 <= y1 + 1; y2++)
            {
                for (int x2 = x1 - 1; x2 <= x1 + 1; x2++)
                {
                    if (0 <= y2 && y2 < data.height && 0 <= x2 && x2 < data.length)
                    {
                        if (Dig(data, y2, x2, false))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Action(Data& data)
{
    int entrance = GetEntrance();

    if (entrance == data.entrances[0] && data.posY > 0)
        (data.posY)--;
    else if (entrance == data.entrances[1] && data.posY < data.height - 1)
        (data.posY)++;
    else if (entrance == data.entrances[2] && data.posX > 0)
        (data.posX)--;
    else if (entrance == data.entrances[3] && data.posX < data.length - 1)
        (data.posX)++;
    else if (entrance == data.entrances[4])
    {
        return Dig(data, data.posY, data.posX, true);
    }
    else if (entrance == data.entrances[5])
        PutFlag(data, data.posY, data.posX);
    else if (entrance == data.entrances[6])
        Pause(data);
    return false;
}

bool FirstDig(Data& data)
{
    if (data.matrix[data.posY][data.posX].isFlag == false)
    {
        GetMine(data);
        for (int y = 0; y < data.height; y++)
        {
            for (int x = 0; x < data.length; x++)
                GetNeightboor(data, y, x);
        }
        for (int y2 = data.posY - 1; y2 <= data.posY + 1; y2++)
        {
            for (int x2 = data.posX - 1; x2 <= data.posX + 1; x2++)
            {
                if (0 <= y2 && y2 < data.height && 0 <= x2 && x2 < data.length)
                {
                    Dig(data, y2, x2, true);
                }
            }
        }
    }
    return false;
}

bool ActionFirstDig(Data& data)
{
    int entrance = GetEntrance();

    if (entrance == data.entrances[0] && data.posY > 0)
        (data.posY)--;
    else if (entrance == data.entrances[1] && data.posY < data.height - 1)
        (data.posY)++;
    else if (entrance == data.entrances[2] && data.posX > 0)
        (data.posX)--;
    else if (entrance == data.entrances[3] && data.posX < data.length - 1)
        (data.posX)++;
    else if (entrance == data.entrances[4])
    {
        return FirstDig(data);
    }
    else if (entrance == data.entrances[5])
        PutFlag(data, data.posY, data.posX);
    else if (entrance == data.entrances[6])
        Pause(data);
    return true;
}

bool PostGame(Data& data, bool isLost)
{
    bool postGame = true; // boucle principale
    int option = 0;
    int* pOption = &option;
    if (isLost)
        Loose(data);
    else
        Win(data);
    while (postGame)
        postGame = postGame = DisplayRestart(data, pOption);
    if (option == 1)
        return false;
    return true;
}

void Game()
{
    Cell** matrix;
    int entrances[] = { 122, 115, 113, 100, 108, 107, 27 }; // up, down, left, rigth , A, B, start
    const char* foregrounds[] = { "\033[36m", "\033[35m", "\033[92m", "\033[33m" };  //cyan, magenta, green, yellow
    const char* backgrounds[] = { "\033[46m", "\033[45m", "\033[102m", "\033[43m" };
    Data data = { 0, 0, nullptr, nullptr, entrances, 0, backgrounds, foregrounds, 0, 0, 0, 0};
    bool running = true;
    while (running)
    {
        Difficulty(data);
        int nbCase = data.height * data.length;
        int nbMine = (nbCase * 15) / 100;
        int nbCaseWin = nbCase - nbMine;
        bool isLost = false;
        bool isWin = false;

        data.matrix = CreateMatrix(data.height, data.length);
        data.cellsToUpdate = CreateArray(16);
        Display(data);

        bool isFirstDig = true; // boucle du premier creusage
        while (isFirstDig)
        {
            Display(data);
            isFirstDig = ActionFirstDig(data);
        }
        bool game = true; // boucle principale
        while (game)
        {
            Display(data);
            isLost = Action(data);
            if (data.nbCaseDug == nbCaseWin)
                isWin = true;
            if (isLost || isWin)
                game = false;
        }
        running = PostGame(data, isLost);
        free(matrix);
        data.nbCaseDug = 0;
    }
}
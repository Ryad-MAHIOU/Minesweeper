#pragma once

struct Cell
{
    bool isDug = false;
    bool isMine = false;
    bool isFlag = false;
    int posX;
    int posY;
    int nbMineAdjacent = 0;
};

Cell** CreateMatrix(int height, int length);
#ifndef CELL_H
#define CELL_H

struct Cell
{
    bool isDug = false;
    bool isMine = false;
    bool isFlag = false;
    int posX;
    int posY;
    int nbMineAdjacent = 0;
};

#endif
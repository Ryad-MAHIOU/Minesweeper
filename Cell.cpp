#pragma once
#include "Cell.h"
#include <iostream>;

Cell** CreateMatrix(int height, int length)
{
    Cell** matrix = (Cell**)malloc(sizeof(Cell*) * height);
    for (int h = 0; h < height; h++)
    {
        matrix[h] = (Cell*)malloc(sizeof(Cell) * length);
        for (int l = 0; l < length; l++)
        {
            matrix[h][l] = Cell();
            matrix[h][l].posY = h;
            matrix[h][l].posX = l;
        }
    }
    return matrix;
}
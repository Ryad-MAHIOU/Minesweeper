#pragma once
#include "Cell.h"

struct CellsToUpdate {
    Cell** array;
    int size;
    int capacity;

    bool IsFullMemory();
    bool IsHalfMemory();
    void AddMemory();
    void RemoveMemory();
    void AddElement(Cell* element);
    void RemoveElement(int index);
    void FreeArray();
};

CellsToUpdate* CreateArray(int capacity);
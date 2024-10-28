#include "CellsToUpdate.h";
#include <iostream>;

bool CellsToUpdate::IsFullMemory()
{
    return (size + 1) * sizeof(Cell*) >= capacity * sizeof(Cell*);
}

bool CellsToUpdate::IsHalfMemory()
{
    return size * 2 <= capacity;
}

void CellsToUpdate::AddMemory()
{
    capacity *= 2;
    array = (Cell**)realloc(array, capacity * sizeof(Cell*));
}

void CellsToUpdate::RemoveMemory()
{
    capacity /= 2;
    array = (Cell**)realloc(array, capacity * sizeof(Cell*));
}

void CellsToUpdate::AddElement(Cell* element)
{
    if (IsFullMemory())
        AddMemory();
    array[size] = element;
    size++;
}

void CellsToUpdate::RemoveElement(int index)
{
    memcpy(array + index, array + index + 1, (size - index - 1) * sizeof(Cell*));
    size--;
    if (IsHalfMemory())
        RemoveMemory();
}

void CellsToUpdate::FreeArray()
{
    size = 0;
    capacity = 0;
    free(array); // Libérer l'array, pas pCellsToUpdate
}

CellsToUpdate* CreateArray(int capacity)
{
    CellsToUpdate* pCellsToUpdate = (CellsToUpdate*)malloc(sizeof(CellsToUpdate));
    pCellsToUpdate->array = (Cell**)malloc(capacity * sizeof(Cell*));
    pCellsToUpdate->size = 0;
    pCellsToUpdate->capacity = capacity;
    return pCellsToUpdate;
}
#pragma once
#include "CellsToUpdate.h"
#include <iostream>;

CellsToUpdate* CreateArray(int capacity)
{
	CellsToUpdate* pCellsToUpdate = (CellsToUpdate*)malloc(sizeof(CellsToUpdate));
	pCellsToUpdate->array = (Cell**)malloc(capacity * sizeof(Cell*));
	pCellsToUpdate->size = 0;
	pCellsToUpdate->capacity = capacity;
	return pCellsToUpdate;
}

bool IsFullMemory(CellsToUpdate* pCellsToUpdate)
{
	if ((pCellsToUpdate->size + 1) * sizeof(int) >= pCellsToUpdate->capacity)
		return true;
	return false;
}

bool IsHalfMemory(CellsToUpdate* pCellsToUpdate)
{
	if (pCellsToUpdate->size * 2 <= pCellsToUpdate->capacity)
		return true;
	return false;
}

void AddMemory(CellsToUpdate* pCellsToUpdate)
{
	pCellsToUpdate->capacity *= 2;
	pCellsToUpdate->array = (Cell**)realloc(pCellsToUpdate->array, pCellsToUpdate->capacity * sizeof(Cell*));
}

void RemoveMemory(CellsToUpdate* pCellsToUpdate)
{
	pCellsToUpdate->capacity /= 2;
	pCellsToUpdate->array = (Cell**)realloc(pCellsToUpdate->array, pCellsToUpdate->capacity * sizeof(Cell*));
}

void AddElement(CellsToUpdate* pCellsToUpdate, Cell* element)
{
	if (IsFullMemory(pCellsToUpdate))
		AddMemory(pCellsToUpdate);
	pCellsToUpdate->array[pCellsToUpdate->size] = element;
	pCellsToUpdate->size++;
}

void RemoveElement(CellsToUpdate* pCellsToUpdate, int index)
{
	memcpy(pCellsToUpdate->array + index, pCellsToUpdate->array + index + 1, (pCellsToUpdate->size - index) * sizeof(Cell*));
	pCellsToUpdate->size--;
	if (IsHalfMemory(pCellsToUpdate))
		RemoveMemory(pCellsToUpdate);
}

void FreeArray(CellsToUpdate* pCellsToUpdate)
{
	pCellsToUpdate->size = 0;
	pCellsToUpdate->capacity = 0;
	free(pCellsToUpdate);
}
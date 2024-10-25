#pragma once
#include "Cell.h"
#include "CellsToUpdate.h"

struct Data
{
	int height;
	int length;
	Cell** matrix;
	CellsToUpdate* cellsToUpdate;
	int* entrances;
	int lastEntrance;
	const char** backgrounds;
	const char** foregrounds;
	int color;
	int nbCaseDug;
	int posX;
	int posY;
};
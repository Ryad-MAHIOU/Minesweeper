#pragma once
#include "Cell.h"
#include "CellsToUpdate.h"

struct Data
{
	// console values
	int heightConsole;
	int lengthConsole;
	// grid values
	int gridPosX;
	int gridPosY;
	int height;
	int length;
	// game
	Cell** matrix;
	CellsToUpdate* cellsToUpdate;
	int lastEntrance;
	int lastPosX;
	int lastPosY;
	int posX;
	int posY;
	int nbCaseDug;
	// settings
	int* entrances;
	const char** backgrounds;
	const char** foregrounds;
	int color;

	void FreeData(Data data);
};
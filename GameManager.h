#pragma once
#include "Data.h";
#include "CellsToUpdate.h";
#include "Cell.h";
#include "DisplayManager.h";
#include "UI.h";

void GetMine(Data& data);
void GetNeightboor(Data& data, int y1, int x1);
void PutFlag(Data& data, int y, int x);
bool Action(Data& data);
bool FirstDig(Data& data);
bool PostGame(Data& data, bool isLost);
void Game();
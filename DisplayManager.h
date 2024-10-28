#pragma once
#include "Data.h";
#include "CellsToUpdate.h";
#include "Cell.h";
#include "ConsoleManager.h";

void Print(char motif, int nb);
bool IsConnect(Data& data, int y, int x);
const char* GetColor(Data& data, int y, int x);
void DisplayLine1(Data& data, int x, int y);
void DisplayLine2(Data& data, int x, int y);
void Display(Data& data);
void UpdatePlayer(Data& data);
void Loose(Data& data);
void Win(Data& data);
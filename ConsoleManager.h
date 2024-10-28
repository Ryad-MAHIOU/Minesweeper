#pragma once
#include "data.h"

int GetEntrance();
void FullScreen();
void MoveCursor(int x, int y);
void HideCursor();
void ClearScreen(int x, int y, int l, int h);
int GetHeightConsole();
int GetLengthConsole();
void GetPosGrid(Data& data);
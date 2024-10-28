#pragma once
#include "Data.h";
#include "ConsoleManager.h";

int GetLength(const char* str);
void DisplayButton(const char* str, const char* foreground, int x, int y, int l);
void Difficulty(Data& data);
bool DisplayRestart(Data& data, int* option);
void Keys(Data& data);
void Themes(Data& data);
void Settings(Data& data);
void Pause(Data& data);
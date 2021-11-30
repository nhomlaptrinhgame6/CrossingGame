#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int LEFT = 42, RIGHT = 109, TOP = 11, BOTTOM = 33;

void DisableResizeWindow();
void ShowScrollbar(BOOL Show);
void GotoXY(int x, int y);
void FixConsoleWindow();

void drawConsole(int x, int y);
void drawMenu(int x, int y);
void runGame();
void Nocursortype();

static int mSpeed = 1;

void clearConsole(int x, int y);
void TextColor(WORD color);
void DisableSelection();
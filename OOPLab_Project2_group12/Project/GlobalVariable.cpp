#include"GlobalVariable.h"

std::wstring Global::mapName = L"basemap";
int Global::remainRound = 20;
int Global::totalPlayer = 4;

House Global::house[28];

std::vector<Player> Global::player;

int Global::currentPlayer = 0;

int Global::stockPrice[3] = { 1000,1000,1000 };
int Global::stockRate[3] = { 0,0,0 };

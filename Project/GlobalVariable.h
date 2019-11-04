#pragma once
#include<string>
#include<vector>
#include"Player.h"
#include"House.h"

class Global
{
public:
	static std::wstring mapName;
	static int remainRound;
	static int totalPlayer;
	static std::vector<Player> player;
	static House house[28];
	static int currentPlayer;

	static int stockPrice[3];
	static int stockRate[3];

};
#pragma once
#include<vector>

class Player
{
public:
	Player();
	~Player();

	bool survive;

	int position;
	int cash;
	std::vector<int> estate;
	int deposit;
	int stock[3] = { 0,0,0 };
	int item[5] = { 0,0,0,0,0 };
	int status;

	int controlDice;//-1:no control

	int calculateAsset();
	void setDeath();
	void walk();
};


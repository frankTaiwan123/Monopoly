#include "Player.h"
#include"GlobalVariable.h"

Player::Player()
{
	position = 0;
	cash = 0;
	deposit = 0;
	status = 0;
	survive = true;
	controlDice = -1;
}

Player::~Player()
{
}

int Player::calculateAsset()
{
	int value = cash + deposit;
	
	for (int i = 0; i < 3; i++)
	{
		value += stock[i] * Global::stockPrice[i];
	}

	for (auto ite = estate.begin(); ite != estate.end(); ite++)
	{
		value += (int)(Global::house[*ite].price*(1 + Global::house[*ite].level / 10.0));
	}

	return value;
}

void Player::setDeath()
{
	deposit = 0;
	cash = 0;
	for (auto ite = estate.begin(); ite != estate.end(); ite++)
	{
		Global::house[*ite].owner = -1;
		Global::house[*ite].level = 0;
	}
	estate.clear();
	for (int i = 0; i < 3; i++)
	{
		stock[i] = 0;
	}
	survive = false;
}

void Player::walk()
{
	position++;
	if (position >= 28)
	{
		position = 0;
	}
}
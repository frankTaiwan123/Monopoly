#include "Bank.h"
#include"GlobalVariable.h"

const int Bank::rate = 5;

Bank::Bank()
{
}
Bank::~Bank()
{
}

int Bank::withdraw(int howMuch)
{
	if (howMuch < 0)
	{
		return -2;
	}
	else if (Global::player[Global::currentPlayer].deposit < howMuch)
	{
		return -1;
	}
	else
	{
		Global::player[Global::currentPlayer].deposit -= howMuch;
		Global::player[Global::currentPlayer].cash += howMuch;
		return 0;
	}
}
int Bank::deposit(int howMuch)
{
	if (howMuch < 0)
	{
		return -2;
	}
	else if (Global::player[Global::currentPlayer].cash < howMuch)
	{
		return -1;
	}
	else
	{
		Global::player[Global::currentPlayer].deposit += howMuch;
		Global::player[Global::currentPlayer].cash -= howMuch;
		return 0;
	}
}

void Bank::payInterest()
{
	for (int i = 0; i < Global::totalPlayer; i++)
	{
		Global::player[i].deposit = (int)(Global::player[i].deposit * (1 + rate / 100.0));
	}
}
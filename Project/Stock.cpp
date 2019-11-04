#include<cstdlib>
#include "Stock.h"
#include"GlobalVariable.h"

Stock::Stock()
{
}
Stock::~Stock()
{
}

void Stock::changePrice()
{
	for (int i = 0; i < 3; i++)
	{
		Global::stockRate[i] = (rand() % 21) - 10;//-10 ~ 10
		Global::stockPrice[i] = (int)(Global::stockPrice[i] * (1 + Global::stockRate[i] / 100.0));
	}
}
int Stock::buy(int which, int howMany)
{
	if (which < 0 || which >= 3 || howMany < 0)
	{
		return -2;
	}
	else if (Global::player[Global::currentPlayer].deposit < (howMany * Global::stockPrice[which]))
	{
		return -1;
	}
	else
	{
		Global::player[Global::currentPlayer].deposit -= (howMany * Global::stockPrice[which]);
		Global::player[Global::currentPlayer].stock[which] += howMany;
		return 0;
	}
}
int Stock::sell(int which, int howMany)
{
	if (which < 0 || which >= 3 || howMany < 0)
	{
		return -2;
	}
	else if (Global::player[Global::currentPlayer].stock[which] < howMany)
	{
		return -1;
	}
	else
	{
		Global::player[Global::currentPlayer].deposit += (howMany * Global::stockPrice[which]);
		Global::player[Global::currentPlayer].stock[which] -= howMany;
		return 0;
	}
}
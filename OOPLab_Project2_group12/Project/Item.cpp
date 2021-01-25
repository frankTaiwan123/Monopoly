#include<algorithm>
#include"GlobalVariable.h"
#include "Item.h"

Item::Item()
{
}
Item::~Item()
{
}

//parameter(use for item 1) default=0(item 0,2,3,4)
int Item::use(int which, int parameterForItem1)
{
	if (which == 0)//遙控骰子
	{
		if (Global::player[Global::currentPlayer].item[0] < 0)
		{
			return -1;
		}

		Global::player[Global::currentPlayer].item[0] -= 1;
		//others in main and Display
		return 0;
	}
	else if (which == 1)//路障
	{
		if (Global::player[Global::currentPlayer].item[1] < 0)
		{
			return -1;
		}

		Global::player[Global::currentPlayer].item[1] -= 1;
		Global::house[parameterForItem1].blocked = true;
		return 0;
	}
	else if (which == 2)//加速卡
	{
		if (Global::player[Global::currentPlayer].item[2] < 0)
		{
			return -1;
		}

		Global::player[Global::currentPlayer].item[2] -= 1;
		Global::player[Global::currentPlayer].status = 1;
		return 0;
	}
	else if (which == 3)//烏龜卡
	{
		if (Global::player[Global::currentPlayer].item[3] < 0)
		{
			return -1;
		}

		Global::player[Global::currentPlayer].item[3] -= 1;
		Global::player[Global::currentPlayer].status = 2;
		return 0;
	}
	else if (which == 4)//購地卡
	{
		int oriOwner = Global::house[Global::player[Global::currentPlayer].position].owner;
		int currentPos = Global::player[Global::currentPlayer].position;
		int buyPrice = (int)(Global::house[currentPos].price*(1 + Global::house[currentPos].level / 10.0));

		if (oriOwner == -1 || oriOwner == Global::currentPlayer)
		{
			return 2;
		}
		if (Global::player[Global::currentPlayer].cash < buyPrice)
		{
			return 1;
		}
		if (Global::player[Global::currentPlayer].item[4] < 0)
		{
			return 1;
		}

		auto ite = std::find(Global::player[oriOwner].estate.begin(), Global::player[oriOwner].estate.end(), currentPos);

		Global::player[Global::currentPlayer].item[4] -= 1;
		Global::player[Global::currentPlayer].cash -= buyPrice;
		Global::player[oriOwner].estate.erase(ite, ite + 1);
		Global::house[currentPos].owner = Global::currentPlayer;
		Global::player[Global::currentPlayer].estate.push_back(currentPos);
		return 0;
	}
	return 0;
}
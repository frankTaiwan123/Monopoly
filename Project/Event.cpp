#include<cstdlib>
#include"GlobalVariable.h"
#include "Event.h"

std::wstring Event::eventNames[10] = {
	L"彩券中獎，獲得10000元",
	L"撿到烏龜卡一張",
	L"贏得比賽，獲得遙控骰子一個",
	L"獲得加速卡效果",
	L"投資失利，損失1000元",
	L"獲得路障",
	L"獲得烏龜卡效果",
	L"隨機傳送",
	L"收到禮物，獲得加速卡一張",
	L"參加抽獎，獲得購地卡一張"
};

int Event::eventCode = 0;

Event::Event()
{
}
Event::~Event()
{
}

void Event::getEvent()
{
	eventCode = rand() % 10;

	switch (eventCode)
	{
	case 0://彩券中獎，獲得10000元
		Global::player[Global::currentPlayer].cash += 10000;
		break;
	case 1://撿到烏龜卡一張
		Global::player[Global::currentPlayer].item[3] += 1;
		break;
	case 2://贏得比賽，獲得遙控骰子一個
		Global::player[Global::currentPlayer].item[0] += 1;
		break;
	case 3://獲得加速卡效果
		Global::player[Global::currentPlayer].status = 1;
		break;
	case 4://投資失利，損失1000元
		if (Global::player[Global::currentPlayer].cash >= 1000)
		{
			Global::player[Global::currentPlayer].cash -= 1000;
		}
		else if (Global::player[Global::currentPlayer].cash < 1000 &&
			(Global::player[Global::currentPlayer].deposit > (1000 - Global::player[Global::currentPlayer].cash)))
		{
			Global::player[Global::currentPlayer].deposit -= (1000 - Global::player[Global::currentPlayer].cash);
			Global::player[Global::currentPlayer].cash = 0;
		}
		else
		{
			Global::player[Global::currentPlayer].setDeath();
		}
		break;
	case 5://獲得路障
		Global::player[Global::currentPlayer].item[1] += 1;
		break;
	case 6://獲得烏龜卡效果
		Global::player[Global::currentPlayer].status = 2;
		break;
	case 7://隨機傳送
		Global::player[Global::currentPlayer].position = rand() % 28;
		break;
	case 8://收到禮物，獲得加速卡一張
		Global::player[Global::currentPlayer].item[2] += 1;
		break;
	case 9://參加抽獎，獲得購地卡一張
		Global::player[Global::currentPlayer].item[4] += 1;
		break;
	}
}
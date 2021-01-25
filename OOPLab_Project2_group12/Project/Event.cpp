#include<cstdlib>
#include"GlobalVariable.h"
#include "Event.h"

std::wstring Event::eventNames[10] = {
	L"�m�餤���A��o10000��",
	L"�ߨ�Q�t�d�@�i",
	L"Ĺ�o���ɡA��o������l�@��",
	L"��o�[�t�d�ĪG",
	L"��ꥢ�Q�A�l��1000��",
	L"��o����",
	L"��o�Q�t�d�ĪG",
	L"�H���ǰe",
	L"����§���A��o�[�t�d�@�i",
	L"�ѥ[����A��o�ʦa�d�@�i"
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
	case 0://�m�餤���A��o10000��
		Global::player[Global::currentPlayer].cash += 10000;
		break;
	case 1://�ߨ�Q�t�d�@�i
		Global::player[Global::currentPlayer].item[3] += 1;
		break;
	case 2://Ĺ�o���ɡA��o������l�@��
		Global::player[Global::currentPlayer].item[0] += 1;
		break;
	case 3://��o�[�t�d�ĪG
		Global::player[Global::currentPlayer].status = 1;
		break;
	case 4://��ꥢ�Q�A�l��1000��
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
	case 5://��o����
		Global::player[Global::currentPlayer].item[1] += 1;
		break;
	case 6://��o�Q�t�d�ĪG
		Global::player[Global::currentPlayer].status = 2;
		break;
	case 7://�H���ǰe
		Global::player[Global::currentPlayer].position = rand() % 28;
		break;
	case 8://����§���A��o�[�t�d�@�i
		Global::player[Global::currentPlayer].item[2] += 1;
		break;
	case 9://�ѥ[����A��o�ʦa�d�@�i
		Global::player[Global::currentPlayer].item[4] += 1;
		break;
	}
}
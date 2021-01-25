#include"GlobalVariable.h"
#include "House.h"

House::House()
{
	type = 0;
	owner = -1;
	location = 0;
	name = L"";
	level = 0;
	price = 0;
	blocked = false;
}
House::~House()
{
}

int House::upgrade()
{
	if (level == 3)
	{
		return -2;
	}
	else if (Global::player[owner].cash < (int)(price*0.1))
	{
		return -1;
	}
	else
	{
		Global::player[owner].cash -= (int)(price*0.1);
		level += 1;
		return 0;
	}
}
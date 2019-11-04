#pragma once
#include<string>
class House
{
public:
	House();
	~House();

	int type;
	int owner;//-1: no owner
	int location;
	std::wstring name;
	int level;
	int price;
	int fee[4] = { 0,0,0,0 };
	bool blocked;

	int upgrade();
};


#pragma once
class Item//item control system
{
public:
	Item();
	~Item();

	static int use(int which, int parameterForItem1 = 0);
};


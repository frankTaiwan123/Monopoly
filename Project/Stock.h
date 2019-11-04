#pragma once
class Stock //stock system(such as stock exchange center)
{
public:
	Stock();
	~Stock();

	static void changePrice();
	static int buy(int which, int howMany);
	static int sell(int which, int howMany);
};


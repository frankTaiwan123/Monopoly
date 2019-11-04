#pragma once
class Bank
{
public:
	Bank();
	~Bank();
	static int withdraw(int howMuch);//´£´Ú
	static int deposit(int howMuch);//¦s´Ú
	static void payInterest();

private:
	static const int rate;
};


#pragma once
class Bank
{
public:
	Bank();
	~Bank();
	static int withdraw(int howMuch);//����
	static int deposit(int howMuch);//�s��
	static void payInterest();

private:
	static const int rate;
};


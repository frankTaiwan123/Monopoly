#pragma once
#include<Windows.h>
#include<io.h>
#include<fcntl.h>
#include<iostream>
#include<string>

enum Color
{
	black = 0,	//  黑色
	D_blue = 1,	//暗藍色(靛色)
	D_green = 2,	//暗綠色
	D_cyan = 3,	//暗青色
	D_red = 4,	//暗紅色(酒紅色)
	D_purple = 5,	//暗紫色
	D_yellow = 6,	//暗黃色(暗金色)
	D_white = 7,	//暗白色(淺灰色)
	gray = 8,	//  灰色(深灰色)
	L_blue = 9,	//亮藍色
	L_green = 10,	//亮綠色
	L_cyan = 11,	//亮青色
	L_red = 12,	//亮紅色
	L_purple = 13,	//亮紫色
	L_yellow = 14,	//亮黃色
	white = 15,	//  白色
};

class Display
{
public:
	Display();
	~Display();
private:
	HANDLE hConsole;
	COORD cursor;
	void outputTextColor(const Color frontColor, const Color bgColor);
public:
	bool setWindowSize(short Width, short Height);
	void cleanScreen();
	void moveCursor(int x, int y);
	void printBeginScreen();
	void printMap();
	void printMenu(bool win = false, int choose = 1);
	void printBank(int player, int choose = 0, std::wstring money = L"0");
	void printStock(int player, int company = 1, int choose = 0, std::wstring money = L"0");
	void printItem(int player, int object = 1, bool selected = false, int choose = 0);
	//setters
	void printMessage(int round, int player);//mode 1
	void printMessage(int throwPoint, int player, bool stopped,
		std::wstring building = L"", int owner = -1, int dollar = 0, int payStatus = 0);//mode 2
	void printMessage(int round, int player, int object, int playerStatus = 0,
		int select = 1, int money = 0, int paymentStatus = 0);//mode 3
	void printMessage(int throwPoint, int player, int eventCode, std::wstring eventMsg);
	void printWinMsg(int player);
};


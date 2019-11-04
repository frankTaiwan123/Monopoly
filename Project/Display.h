#pragma once
#include<Windows.h>
#include<io.h>
#include<fcntl.h>
#include<iostream>
#include<string>

enum Color
{
	black = 0,	//  �¦�
	D_blue = 1,	//�t�Ŧ�(�Q��)
	D_green = 2,	//�t���
	D_cyan = 3,	//�t�C��
	D_red = 4,	//�t����(�s����)
	D_purple = 5,	//�t����
	D_yellow = 6,	//�t����(�t����)
	D_white = 7,	//�t�զ�(�L�Ǧ�)
	gray = 8,	//  �Ǧ�(�`�Ǧ�)
	L_blue = 9,	//�G�Ŧ�
	L_green = 10,	//�G���
	L_cyan = 11,	//�G�C��
	L_red = 12,	//�G����
	L_purple = 13,	//�G����
	L_yellow = 14,	//�G����
	white = 15,	//  �զ�
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


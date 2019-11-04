#include<cstdlib>
#include<time.h>
#include"Bank.h"
#include"Display.h"
#include"Event.h"
#include"File.h"
#include"GlobalVariable.h"
#include"House.h"
#include"Item.h"
#include"KeyInput.h"
#include"Player.h"
#include"Stock.h"
using namespace std;

Display output;

int checkWin();
int selectMenu(bool win);
int throwDice(int base);
void nextPlayer();

int main()
{
	//initialize variable
	srand((unsigned int)time(NULL));
	output.setWindowSize(98, 52);
	

	//start program
	//print begin screen
	output.printBeginScreen();
	output.moveCursor(79, 17);
	while (keyInput::readKey() != 0x0D/*Enter*/)
	{
		//do nothing
	}

	//check file and read
	if (!File::readFile(".\\stroageFile\\basemap.txt"))
	{
		File::readFile(".\\originalFile\\basemap.txt");
		File::writeFile(".\\stroageFile\\basemap.txt");
	}
	//end read file

	RESTART:

	File::readFile(".\\stroageFile\\basemap.txt");

	//main loop
	int winner;
	char key;
	output.printMap();
	while (true)
	{
		//win
		if ((winner = checkWin()) != -1)
		{
			int select = 4;
			output.printMap();
			output.printWinMsg(winner+1);
			output.printMenu(true,select);
			
			//select menu
			select = selectMenu(true);
			//end select menu

			//action
			//restart
			if (select == 4)
			{
				//initialize
				File::readFile(".\\originalFile\\basemap.txt");
				File::writeFile(".\\stroageFile\\basemap.txt");

				goto RESTART;
			}
			//end restart
			//quit
			else if (select == 5)
			{
				File::writeFile(".\\stroageFile\\basemap.txt");
				return 0;
			}
			//end quit
			//end action
		}
		//end win
		//not win(normal game)
		else
		{
			output.printMap();
			output.printMessage(Global::remainRound, Global::currentPlayer+1);
			output.moveCursor(55, 47);
			
			key = keyInput::readKey();
			//throwDice
			if (key == 0x0D/*Enter*/)
			{
				//throw dice
				int baseDice = 6;
				if (Global::player[Global::currentPlayer].status == 1)//speed up
				{
					baseDice = 12;
				}
				else if (Global::player[Global::currentPlayer].status == 2)//turtle
				{
					baseDice = 3;
				}
				int point = throwDice(baseDice);

				if (Global::player[Global::currentPlayer].controlDice != -1)
				{
					point = Global::player[Global::currentPlayer].controlDice;
				}

				Global::player[Global::currentPlayer].status = 0;

				output.printMap();
				output.printMessage(point, Global::currentPlayer, false);
				//end throw dice
				//walk
				for (int i = 0; i < point; i++)
				{
					Global::player[Global::currentPlayer].walk();
					output.printMap();
					output.printMessage(point, Global::currentPlayer, false);
					if (Global::house[Global::player[Global::currentPlayer].position].type == 0)//pass start
					{
						Global::player[Global::currentPlayer].cash += 2000;
						//message?
					}
					if (Global::house[Global::player[Global::currentPlayer].position].blocked)//barrior
					{
						Global::house[Global::player[Global::currentPlayer].position].blocked = false;
						//message?
						break;
					}
				}
				//end walk
				//land action
				if (Global::house[Global::player[Global::currentPlayer].position].type == 0)//start
				{
					//message?
				}
				else if (Global::house[Global::player[Global::currentPlayer].position].type < 0)//event
				{
					Event::getEvent();
					output.printMap();
					output.printMessage(point, Global::currentPlayer+1, 
						2 - Global::house[Global::player[Global::currentPlayer].position].type, 
						Event::eventNames[Event::eventCode]);
					while (keyInput::readKey() != 0x0D/*Enter*/)
					{
						//do nothing
					}
				}
				else if (Global::house[Global::player[Global::currentPlayer].position].owner == -1)//free land
				{
					output.printMap();
					output.printMessage(point, Global::currentPlayer + 1, true,
						Global::house[Global::player[Global::currentPlayer].position].name, -1,
						Global::house[Global::player[Global::currentPlayer].position].price);
					char k;
					while (true)
					{
						k = keyInput::readKey();
						if (k == 'y')
						{
							int payStatus;
							if (Global::player[Global::currentPlayer].cash < 
								Global::house[Global::player[Global::currentPlayer].position].price)
							{
								payStatus = 3;
							}
							else
							{
								Global::player[Global::currentPlayer].cash -= Global::house[Global::player[Global::currentPlayer].position].price;
								Global::house[Global::player[Global::currentPlayer].position].owner = Global::currentPlayer;
								Global::player[Global::currentPlayer].estate.push_back(Global::player[Global::currentPlayer].position);
								payStatus = 1;
							}
							output.printMap();
							output.printMessage(point, Global::currentPlayer + 1, true,
								Global::house[Global::player[Global::currentPlayer].position].name, -1,
								Global::house[Global::player[Global::currentPlayer].position].price, payStatus);
							break;
						}
						else if (k == 'n')
						{
							output.printMap();
							output.printMessage(point, Global::currentPlayer + 1, true,
								Global::house[Global::player[Global::currentPlayer].position].name, -1,
								Global::house[Global::player[Global::currentPlayer].position].price,2);
							break;
						}
					}
					while (keyInput::readKey() != 0x0D/*Enter*/)
					{
						//do nothing
					}
				}
				else if (Global::house[Global::player[Global::currentPlayer].position].owner == Global::currentPlayer)
					//self land
				{
					output.printMap();
					output.printMessage(point, Global::currentPlayer + 1, true,
						Global::house[Global::player[Global::currentPlayer].position].name, Global::currentPlayer + 1,
						int(Global::house[Global::player[Global::currentPlayer].position].price * 0.1));
					char k;
					while (true)
					{
						k = keyInput::readKey();
						if (k == 'y')
						{
							int payStatus;
							int status = Global::house[Global::player[Global::currentPlayer].position].upgrade();
							if (status == -2)
							{
								payStatus = 4;
							}
							else if (status == -1)
							{
								payStatus = 3;
							}
							else
							{
								
								payStatus = 1;
							}
							output.printMap();
							output.printMessage(point, Global::currentPlayer + 1, true,
								Global::house[Global::player[Global::currentPlayer].position].name, Global::currentPlayer + 1,
								int(Global::house[Global::player[Global::currentPlayer].position].price * 0.1), payStatus);
							break;
						}
						else if (k == 'n')
						{
							output.printMap();
							output.printMessage(point, Global::currentPlayer + 1, true,
								Global::house[Global::player[Global::currentPlayer].position].name, Global::currentPlayer + 1,
								Global::house[Global::player[Global::currentPlayer].position].price, 2);
							break;
						}
					}
					while (keyInput::readKey() != 0x0D/*Enter*/)
					{
						//do nothing
					}
				}
				else //other's land
				{
					int oriOwner = Global::house[Global::player[Global::currentPlayer].position].owner;
					int level = Global::house[Global::player[Global::currentPlayer].position].level;
					int fee = Global::house[Global::player[Global::currentPlayer].position].fee[level];

					output.printMap();
					output.printMessage(point, Global::currentPlayer + 1, true,
						Global::house[Global::player[Global::currentPlayer].position].name, oriOwner + 1,fee);

					if (Global::player[Global::currentPlayer].cash >= fee)
					{
						Global::player[Global::currentPlayer].cash -= fee;
						Global::player[oriOwner].cash += fee;
						output.printMap();
						output.printMessage(point, Global::currentPlayer + 1, true,
							Global::house[Global::player[Global::currentPlayer].position].name, oriOwner + 1, fee,1);
					}
					else if (Global::player[Global::currentPlayer].deposit >= fee - Global::player[Global::currentPlayer].cash)
					{
						Global::player[Global::currentPlayer].deposit-= (fee - Global::player[Global::currentPlayer].cash);
						Global::player[Global::currentPlayer].cash = 0;
						Global::player[oriOwner].cash += fee;
						output.printMap();
						output.printMessage(point, Global::currentPlayer + 1, true,
							Global::house[Global::player[Global::currentPlayer].position].name, oriOwner + 1, fee, 1);
					}
					else
					{
						Global::player[Global::currentPlayer].setDeath();
						Global::player[oriOwner].cash += fee;
						//message?
						output.printMap();
						output.printMessage(point, Global::currentPlayer + 1, true,
							Global::house[Global::player[Global::currentPlayer].position].name, oriOwner + 1, fee, 1);
					}
					while (keyInput::readKey() != 0x0D/*Enter*/)
					{
						//do nothing
					}
				}
				//end land action

				//next round
				//next player
				nextPlayer();
				//end next player
				Stock::changePrice();
				Global::remainRound--;
				if (Global::remainRound % 5 == 0)
				{
					Bank::payInterest();
				}
				
				File::writeFile(".\\stroageFile\\basemap.txt");//stoage file
				//end next round
			}
			//end throwDice
			//menu
			else if (key == 0x1B/*ESC*/)
			{
				int menuSelect = 1;
				output.printMenu(false, menuSelect);
				//select menu
				menuSelect = selectMenu(false);
				//end select menu

				//action
				if (menuSelect == -1)//esc
				{
					output.printMap();
				}
				//bank
				if (menuSelect == 1)
				{
					output.printBank(Global::currentPlayer+1);

					char k;
					int select = 0;
					wstring money = L"0";

					while (true)
					{
						k = keyInput::readKey();
						if (k == 0x1B/*ESC*/)
						{
							break;
						}
						if (k == 0x4B/*LEFT*/)
						{
							select--;
							if (select < 0)
							{
								select = 1;
							}
							output.printBank(Global::currentPlayer+1, select, money);
						}
						if (k == 0x4D/*RIGHT*/)
						{
							select++;
							if (select > 1)
							{
								select = 0;
							}
							output.printBank(Global::currentPlayer + 1, select, money);
						}
						if (k == 8/*backspace*/)
						{
							if (money.length() != 0)
							{
								money.erase(money.end() - 1);
							}
							output.printBank(Global::currentPlayer + 1, select, money);
						}
						if (k >= 48/*0*/ && k <= 57/*9*/)
						{
							if (money == L"0")
							{
								money = k;
							}
							else
							{
								money += k;
							}
							output.printBank(Global::currentPlayer + 1, select, money);
						}
						if (k == 0x0D/*ENTER*/)
						{
							int code;
							if (select == 0)
							{
								code = Bank::deposit(stoi(money));
							}
							else if(select == 1)
							{
								code = Bank::withdraw(stoi(money));
							}
							//message?

							output.printMap();
							money = L"0";
							output.printBank(Global::currentPlayer + 1, select, L"0");
						}
					}
				}
				//end bank
				//stock
				else if (menuSelect == 2)
				{
					output.printStock(Global::currentPlayer + 1);

					char k;
					int company = 1;
					int select = 0;
					wstring money = L"0";

					while (true)
					{
						k = keyInput::readKey();
						if (k == 0x1B/*ESC*/)
						{
							break;
						}
						if (k == 0x4B/*LEFT*/)
						{
							select--;
							if (select < 0)
							{
								select = 1;
							}
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
						if (k == 0x4D/*RIGHT*/)
						{
							select++;
							if (select > 1)
							{
								select = 0;
							}
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
						if (k == 0x48/*UP*/)
						{
							company--;
							if (company < 1)
							{
								company = 3;
							}
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
						if (k == 0x50/*DOWN*/)
						{
							company++;
							if (company > 3)
							{
								company = 1;
							}
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
						if (k == 8/*backspace*/)
						{
							if (money.length() != 0)
							{
								money.erase(money.end() - 1);
							}
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
						if (k >= 48/*0*/ && k <= 57/*9*/)
						{
							if (money == L"0")
							{
								money = k;
							}
							else
							{
								money += k;
							}
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
						if (k == 0x0D/*ENTER*/)
						{
							int code;
							if (select == 0)
							{
								code = Stock::buy(company - 1, stoi(money));
							}
							else if (select == 1)
							{
								code = Stock::sell(company - 1, stoi(money));
							}
							//message?

							output.printMap();
							money = L"0";
							output.printStock(Global::currentPlayer + 1, company, select, money);
						}
					}
				}
				//end stock
				//item
				else if (menuSelect == 3)
				{
					output.printItem(Global::currentPlayer);

					char k;
					int item = 0;
					
					while (true)
					{
						k = keyInput::readKey();
						if (k == 0x1B/*ESC*/)
						{
							break;
						}
						if (k == 0x48/*UP*/)
						{
							item--;
							if (item < 0)
							{
								item = 4;
							}
							output.printItem(Global::currentPlayer, item + 1, false);
						}
						if (k == 0x50/*DOWN*/)
						{
							item++;
							if (item > 4)
							{
								item = 0;
							}
							output.printItem(Global::currentPlayer, item + 1, false);
						}
						if (k == 0x0D/*ENTER*/)
						{
							output.printItem(Global::currentPlayer, item + 1, true);

							char c;
							int select = 0;

							while (true)
							{
								c = keyInput::readKey();
								if (c == 0x48/*UP*/)
								{
									select--;
									if (select < 0)
									{
										select = 1;
									}
									output.printItem(Global::currentPlayer, item + 1, true,select);
								}
								if (c == 0x50/*DOWN*/)
								{
									select++;
									if (select > 1)
									{
										select = 0;
									}
									output.printItem(Global::currentPlayer, item + 1, true, select);
								}
								if (c == 0x0D/*ENTER*/)
								{
									break;
								}
							}
							
							//use item
							if (select == 0)
							{
								int player = Global::currentPlayer;
								//control dice
								if (item == 0)
								{
									int status = Global::player[player].status;
									output.printMessage(Global::remainRound, player, 1, status);

									int choose = 1;
									int maxPoint = 6 * (status == 0) + 12 * (status == 1) + 3 * (status == 2);
									while (true)
									{
										c = keyInput::readKey();
										if (c == 0x4B/*LEFT*/)
										{
											choose--;
											if (choose < 1)
											{
												choose = maxPoint;
											}
											output.printMessage(Global::remainRound, player, 1, status, choose);
										}
										if (c == 0x4D/*RIGHT*/)
										{
											choose++;
											if (choose > maxPoint)
											{
												choose = 1;
											}
											output.printMessage(Global::remainRound, player, 1, status, choose);
										}
										if (c == 0x0D/*ENTER*/)
										{
											Global::player[player].controlDice = choose;
											Item::use(0);
											break;
										}
									}
									
								}
								//end control dice
								//barrior
								else if (item == 1)//place only at the position that player stay
								{
									Item::use(1, Global::player[Global::currentPlayer].position);
									output.printMessage(Global::remainRound, player, 2);
								}
								//end barrior
								//speed up
								else if (item == 2)
								{
									Item::use(2);
									output.printMessage(Global::remainRound, player, 3);
									while (keyInput::readKey() != 0x0D/*Enter*/)
									{
										//do nothing
									}
								}
								//end speed up
								//turtle
								else if (item == 3)
								{
									Item::use(3);
									output.printMessage(Global::remainRound, player, 4);
									while (keyInput::readKey() != 0x0D/*Enter*/)
									{
										//do nothing
									}
								}
								//end turtle
								//buy estate
								else if (item == 4)
								{
									int currentPos = Global::player[Global::currentPlayer].position;
									int buyPrice = (int)(Global::house[currentPos].price*(1 + Global::house[currentPos].level / 10.0));
									
									int code = Item::use(4);
									output.printMessage(Global::remainRound, player, 5, 0, 1, buyPrice, code);
									while (keyInput::readKey() != 0x0D/*Enter*/)
									{
										//do nothing
									}
								}
								//end buy estate
							}
							//end use item

							output.printMap();
							output.printItem(Global::currentPlayer, item + 1, false);
						}
					}
					
				}
				//end item
				//restart
				else if (menuSelect == 4)
				{
					//initialize
					File::readFile(".\\originalFile\\basemap.txt");
					File::writeFile(".\\stroageFile\\basemap.txt");

					goto RESTART;
				}
				//end restart
				//quit
				else if (menuSelect == 5)
				{
					File::writeFile(".\\stroageFile\\basemap.txt");
					return 0;
				}
				//end quit
				//end action
			}
			//end menu
		}
		//end not win
	}
	//end main loop
}//end main

int checkWin()
{
	int countSurvive = 0;
	for (int i = 0; i < Global::totalPlayer; i++)
	{
		if (Global::player[i].survive)
		{
			countSurvive++;
		}
	}

	int winner;
	if (Global::remainRound == 0)
	{
		//find most rich player
		int richPlayer = 0;
		int asset = 0;
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			if (Global::player[i].survive && Global::player[i].calculateAsset() > asset)
			{
				richPlayer = i;
				asset = Global::player[i].calculateAsset();
			}
		}
		winner = richPlayer;
	}
	else if (countSurvive == 0)
	{
		winner = 0;
	}
	else if (countSurvive == 1)
	{
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			if (Global::player[i].survive)
			{
				winner = i;
				break;
			}
		}
	}
	else
	{
		winner = -1;
	}

	return winner;
}
int selectMenu(bool win)
{
	int leftBond = 1, rightBond = 5;
	if (win)
	{
		leftBond = 4;
	}

	int select = leftBond;
	while (true)
	{
		char key = keyInput::readKey();
		if (key == 0x48/*UP*/)
		{
			select -= 1;
			if (select < leftBond)
			{
				select = rightBond;
			}
			output.printMenu(win, select);
		}
		else if (key == 0x50/*DOWN*/)
		{
			select += 1;
			if (select > rightBond)
			{
				select = leftBond;
			}
			output.printMenu(win, select);
		}
		else if (key == 0x0D/*Enter*/)
		{
			break;
		}
		if (!win && key == 0x1B/*ESC*/)
		{
			select = -1;
			break;
		}
	}

	return select;
}
int throwDice(int base)
{
	return rand() % base + 1;
}
void nextPlayer()
{
	int current = Global::currentPlayer;
	current++;

	while (true)
	{
		if (current > Global::totalPlayer - 1)
		{
			current = 0;
		}
		else if (!Global::player[current].survive)
		{
			current++;
		}
		else
		{
			break;
		}
	}

	Global::currentPlayer = current;
}

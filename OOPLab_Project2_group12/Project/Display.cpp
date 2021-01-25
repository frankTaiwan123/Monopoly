#include "Display.h"
#include"GlobalVariable.h"
#include"Bank.h"

Display::Display()
{
	//將輸出設為unicoode 形式
	_setmode(_fileno(stdout), _O_WTEXT);

	//取得輸出handle，當需要改輸出設定時使用
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//initialize cursor's pos
	moveCursor(0, 0);

	//將文字輸出設為黑底白字
	outputTextColor(Color::D_white, Color::black);
}


Display::~Display()
{
	//nothing
}


void Display::outputTextColor(const Color frontColor, const Color bgColor)
{
	int colorIndex = bgColor * 16 + frontColor;
	SetConsoleTextAttribute(hConsole, colorIndex);
}


bool Display::setWindowSize(short Width, short Height)
{
	COORD NewSBSize = GetLargestConsoleWindowSize(hConsole);
	if (Width >= NewSBSize.X) {
		Width = NewSBSize.X - 1;
	}
	if (Height >= NewSBSize.Y) {
		Height = NewSBSize.Y - 1;
	}
	//CanvasWidth = Width / 2;
	//CanvasHeight = Height;
	SMALL_RECT windowSize = { 0, 0, Width, Height };
	SetConsoleScreenBufferSize(hConsole, NewSBSize);
	//InitCanvas();
	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize))
	{
		std::wcout << "SetConsoleWindowInfo failed with error " << GetLastError() << std::endl;
		return false;
	}
	return true;
}


void Display::cleanScreen()
{
	outputTextColor(Color::D_white, Color::black);
	system("cls");
}


void Display::moveCursor(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(hConsole, cursor);
}


void Display::printBeginScreen()
{
	const std::wstring canvus[21] = {
		L"                                                                                                  ",
		L"                                                                                                  ",
		L"             M   M      OOO      N   N      OOO      PPPP       OOO      L        Y   Y           ",
		L"             MM MM     O   O     NN  N     O   O     P   P     O   O     L         Y Y            ",
		L"             M M M     O   O     N N N     O   O     PPPP      O   O     L          Y             ",
		L"             M   M     O   O     N  NN     O   O     P         O   O     L          Y             ",
		L"             M   M      OOO      N   N      OOO      P          OOO      LLLL       Y             ",
		L"                                                                                                  ",
		L"                                                                                                  ",
		L"                               __                           _                                     ",
		L"                             ∕__  ._   _        ._     /|   )                                    ",
		L"                             ∖_|  |   (_)  |_|  |_)    _|_ /_                                    ",
		L"                                                 |                                                ",
		L"                                                                                                  ",
		L"                                                                                                  ",
		L"                _                 __                                         |                    ",
		L"               |_)  _ _  _  _    |_  _  _|_ _   _   _|_ _     _ _|_ _  .__|_ |                    ",
		L"               |   | (/__> _>    |__| |  |_(/_ |     |_(_)   _>  |_(/| |  |_ o                    ",
		L"                                                                                                  ",
		L"                                                                                                  ",
		L"                                                                                                  "
	};

	outputTextColor(Color::D_yellow, Color::white);
	for (int i = 0; i < 21; i++)
	{
		moveCursor(0, i + 0);
		std::wcout << canvus[i];
	}

	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}


void Display::printMap()
{
	const std::wstring userInfo[8] = {
		L"╔═══════════╤═══════════╤═══════════╤═══════════╗",
		L"║           1          │           2          │           3          │           4          ║",
		L"╠═══════════╪═══════════╪═══════════╪═══════════╣",
		L"║      現金:           │      現金:           │      現金:           │      現金:           ║",
		L"║      存款:           │      存款:           │      存款:           │      存款:           ║",
		L"║  股票價值:           │  股票價值:           │  股票價值:           │  股票價值:           ║",
		L"║  房產價值:           │  房產價值:           │  房產價值:           │  房產價值:           ║",
		L"╚═══════════╧═══════════╧═══════════╧═══════════╝"
	};
	const std::wstring map[33] = {
		L"╔═════╤═════╤═════╤═════╤═════╤═════╤═════╤═════╗",
		L"║   　　   │   　　   │   　　   │   　　   │   　　   │   　　   │   　　   │   　　   ║",
		L"║  | || |  │  | || |  │  | || |  │  | || |  │  | || |  │  | || |  │  | || |  │  | || |  ║",
		L"║          │          │          │          │          │          │          │          ║",
		L"╠─────┼─────┴─────┴─────┴─────┴─────┴─────┼─────╣",
		L"║   　　   │                                                                      │   　　   ║",
		L"║  | || |  │                                                                      │  | || |  ║",
		L"║          │        __ __  _____  __  __  _____  _____  _____  __     __ __       │          ║",
		L"╠─────┤       |  V  ||  _  ||  ∖| ||  _  ||  _  ||  _  ||  |   |  |  |      ├─────╣",
		L"║   　　   │       | | | || |_| || |  | || |_| ||   __|| |_| ||  |__ ∖   /       │   　　   ║",
		L"║  | || |  │       |_|_|_||_____||_|∖__||_____||__|   |_____||_____|  |_|        │  | || |  ║",
		L"║          │                                                                      │          ║",
		L"╠─────┤                                                                      ├─────╣",
		L"║   　　   │                                                                      │   　　   ║",
		L"║  | || |  │                                                                      │  | || |  ║",
		L"║          │                                                                      │          ║",
		L"╠─────┤                                                                      ├─────╣",
		L"║   　　   │                              ___________                             │   　　   ║",
		L"║  | || |  │                             /   __     /|                            │  | || |  ║",
		L"║          │                            /   /_     / |                            │          ║",
		L"╠─────┤                           /    __/   /  |                            ├─────╣",
		L"║   　　   │                          /__________/ | |                            │   　　   ║",
		L"║  | || |  │                          |    _     | | /                            │  | || |  ║",
		L"║          │                          |   |_     |  /                             │          ║",
		L"╠─────┤                          |   |_|    | /                              ├─────╣",
		L"║   　　   │                          |__________|/                               │   　　   ║",
		L"║  | || |  │                                                                      │  | || |  ║",
		L"║          │                                                                      │          ║",
		L"╠─────┼─────┬─────┬─────┬─────┬─────┬─────┼─────╣",
		L"║   　　   │   　　   │   　　   │   　　   │   　　   │   　　   │   　　   │   　　   ║",
		L"║  | || |  │  | || |  │  | || |  │  | || |  │  | || |  │  | || |  │  | || |  │  | || |  ║",
		L"║          │          │          │          │          │          │          │          ║",
		L"╚═════╧═════╧═════╧═════╧═════╧═════╧═════╧═════╝"
	};
	const std::wstring info[11] = {
		L"╔═══════════════════════════════════════════════╗",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"║                                                                                              ║",
		L"╚═══════════════════════════════════════════════╝"
	};

	//user info
	outputTextColor(Color::D_cyan, Color::L_yellow);
	for (int i = 0; i < 8; i++)
	{
		moveCursor(0, i + 0);
		std::wcout << userInfo[i];
	}

	moveCursor(2, 1);
	if (Global::player[0].survive)
	{
		outputTextColor(Color::black, Color::L_blue);
	}
	else
	{
		outputTextColor(Color::white, Color::gray);
	}
	std::wcout << L"           1          ";

	moveCursor(26, 1);
	if (Global::totalPlayer>=2 && Global::player[1].survive)
	{
		outputTextColor(Color::black, Color::L_green);
	}
	else
	{
		outputTextColor(Color::white, Color::gray);
	}
	std::wcout << L"           2          ";

	moveCursor(50, 1);
	if (Global::totalPlayer >= 3 && Global::player[2].survive)
	{
		outputTextColor(Color::black, Color::L_cyan);
	}
	else
	{
		outputTextColor(Color::white, Color::gray);
	}
	std::wcout << L"           3          ";

	moveCursor(74, 1);
	if (Global::totalPlayer >= 4 && Global::player[3].survive)
	{
		outputTextColor(Color::black, Color::L_red);
	}
	else
	{
		outputTextColor(Color::white, Color::gray);
	}
	std::wcout << L"           4          ";

	
	for (int i = 0; i < Global::totalPlayer; i++)
	{
		if (!Global::player[i].survive)
		{
			outputTextColor(Color::white, Color::gray);
			moveCursor(2 + 24 * i, 3);
			std::wcout << L"      現金:           ";
			moveCursor(2 + 24 * i, 4);
			std::wcout << L"      存款:           ";
			moveCursor(2 + 24 * i, 5);
			std::wcout << L"  股票價值:           ";
			moveCursor(2 + 24 * i, 6);
			std::wcout << L"  房產價值:           ";

			moveCursor(14 + 24 * i, 3);
			std::wcout << Global::player[i].cash;

			moveCursor(14 + 24 * i, 4);
			std::wcout << Global::player[i].deposit;

			moveCursor(14 + 24 * i, 5);
			int stockValue = 0;
			for (int j = 0; j < 3; j++)
			{
				stockValue += Global::player[i].stock[j] * Global::stockPrice[j];
			}
			std::wcout << stockValue;

			moveCursor(14 + 24 * i, 6);
			int estateValue = 0;
			for (auto ite = Global::player[i].estate.begin(); ite != Global::player[i].estate.end(); ite++)
			{
				estateValue += (int)(Global::house[*ite].price*(1 + Global::house[*ite].level / 10.0));
			}
			std::wcout << estateValue;
		}
		else
		{
			outputTextColor(Color::D_cyan, Color::L_yellow);

			moveCursor(14 + 24 * i, 3);
			std::wcout << Global::player[i].cash;

			moveCursor(14 + 24 * i, 4);
			std::wcout << Global::player[i].deposit;

			moveCursor(14 + 24 * i, 5);
			int stockValue = 0;
			for (int j = 0; j < 3; j++)
			{
				stockValue += Global::player[i].stock[j] * Global::stockPrice[j];
			}
			std::wcout << stockValue;

			moveCursor(14 + 24 * i, 6);
			int estateValue = 0;
			for (auto ite = Global::player[i].estate.begin(); ite != Global::player[i].estate.end(); ite++)
			{
				estateValue += (int)(Global::house[*ite].price*(1 + Global::house[*ite].level / 10.0));
			}
			std::wcout << estateValue;
		}
	}
	//end user info

	//map
	outputTextColor(Color::black, Color::white);
	for (int i = 0; i < 33; i++)
	{
		moveCursor(0, i + 8);
		std::wcout << map[i];
	}

	const int pos[28][2] = {
		{3,1 + 8},{15,1 + 8},{27,1 + 8},{39,1 + 8},{51,1 + 8},{63,1 + 8},{75,1 + 8},
		{87,1 + 8},{87,5 + 8},{87,9 + 8},{87,13 + 8},{87,17 + 8},{87,21 + 8},{87,25 + 8},
		{87,29 + 8},{75,29 + 8},{63,29 + 8},{51,29 + 8},{39,29 + 8},{27,29 + 8},{15,29 + 8},
		{3,29 + 8},{3,25 + 8},{3,21 + 8},{3,17 + 8},{3,13 + 8},{3,9 + 8},{3,5 + 8}
	};
	for (int i = 0; i < 28; i++)
	{
		//name
		moveCursor(pos[i][0], pos[i][1]);
		std::wstring name = Global::house[i].name;
		int owner= Global::house[i].owner;

		if (name.length() > 4)
		{
			name.erase(name.begin() + 4);
		}
		else if (name.length() == 3)
		{
			name = L" " + name + L" ";
		}
		else if (name.length() == 2)
		{
			name = L"  " + name + L"  ";
		}
		else if (name.length() == 1)
		{
			name = L"   " + name + L"   ";
		}

		if (owner == 0)
		{
			outputTextColor(Color::black, Color::L_blue);
		}
		else if (owner == 1)
		{
			outputTextColor(Color::black, Color::L_green);
		}
		else if (owner == 2)
		{
			outputTextColor(Color::black, Color::L_cyan);
		}
		else if (owner == 3)
		{
			outputTextColor(Color::black, Color::L_red);
		}
		else
		{
			outputTextColor(Color::black, Color::white);
		}
		std::wcout << name;
		//end name
		//info
		outputTextColor(Color::black, Color::white);
		moveCursor(pos[i][0] - 1, pos[i][1] + 2);
		if (Global::house[i].blocked)
		{
			std::wcout << L"※";
		}
		else
		{
			std::wcout << L"  ";
		}
		outputTextColor(Color::black, Color::white);
		moveCursor(pos[i][0] + 2, pos[i][1] + 2);
		if (Global::house[i].type == 1)
		{
			std::wcout << L"$" << Global::house[i].price;
		}
		//end info
	}
	
	for (int i = 0; i < Global::totalPlayer; i++)
	{
		moveCursor(pos[Global::player[i].position][0] + 2*i + 1*(i>=2), pos[Global::player[i].position][1] + 1);
		if (i == 0)
		{
			outputTextColor(Color::white, Color::L_blue);
		}
		else if (i == 1)
		{
			outputTextColor(Color::black, Color::L_green);
		}
		else if (i == 2)
		{
			outputTextColor(Color::black, Color::L_cyan);
		}
		else if (i == 3)
		{
			outputTextColor(Color::white, Color::L_red);
		}

		std::wcout << i + 1;
	}
	//end map

	//info
	outputTextColor(Color::black, Color::L_cyan);
	for (int i = 0; i < 11; i++)
	{
		moveCursor(0, i + 41);
		std::wcout << info[i];
	}
	//end info

	moveCursor(0, 52);
	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}

//win default=false
//choose: 1,2,3,4,5 default=1
void Display::printMenu(bool win, int choose)
{
	const std::wstring menu[9] = {
		L"╔═════╗",
		L"║   選單   ║",
		L"╠─────╣",
		L"║   銀行　 ║",
		L"║   股票   ║",
		L"║  物品欄  ║",
		L"║ 重新開始 ║",
		L"║ 結束遊戲 ║",
		L"╚═════╝"
	};

	//prevent out of range
	if (win)
	{
		if (choose < 4)
		{
			choose = 4;
		}
		else if (choose > 5)
		{
			choose = 5;
		}
	}
	else
	{
		if (choose < 1)
		{
			choose = 1;
		}
		else if (choose > 5)
		{
			choose = 5;
		}
	}

	outputTextColor(Color::black, Color::L_yellow);
	for (int i = 0; i < 9; i++)
	{
		moveCursor(42, i + 18);
		std::wcout << menu[i];
	}

	if (win)
	{
		outputTextColor(Color::black, Color::L_yellow);
		moveCursor(47, 1 + 18);
		std::wcout << L"獲勝";

		outputTextColor(Color::white, Color::L_yellow);

		for (int i = 1; i <= 3; i++)
		{
			moveCursor(44, i + 20);
			std::wcout << menu[i + 2].substr(1, menu[i + 2].length() - 2);
		}
	}

	outputTextColor(Color::white, Color::L_blue);
	moveCursor(44, choose + 20);
	std::wcout << menu[choose + 2].substr(1, menu[choose + 2].length() - 2);

	moveCursor(0, 52);
	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}

//choose:0,1 default=0
//money default=L"0"
void Display::printBank(int player, int choose, std::wstring money)
{
	const std::wstring bank[33] = {
		L"      ╔═════════════════════════════════════════╗      ",
		L"      ║                   ____        _                                                  ║      ",
		L"      ║                  |    >     ∕ ∖       |∖  |      |  ∕                        ║      ",
		L"      ║                  |---<     ∕---∖      | ∖ |      |-<                          ║      ",
		L"      ║                  |____>   ∕     ∖     |  ∖|      |  ∖                        ║      ",
		L"      ║        玩家                    目前存款                        下期利息          ║      ",
		L"      ╠──────────┬───────────────┬──────────────╣      ",
		L"      ║                    │                              │                            ║      ",
		L"      ║         1          │                              │                            ║      ",
		L"      ║                    │                              │                            ║      ",
		L"      ╠──────────┼───────────────┼──────────────╣      ",
		L"      ║                    │                              │                            ║      ",
		L"      ║         2          │                              │                            ║      ",
		L"      ║                    │                              │                            ║      ",
		L"      ╠──────────┼───────────────┼──────────────╣      ",
		L"      ║                    │                              │                            ║      ",
		L"      ║         3          │                              │                            ║      ",
		L"      ║                    │                              │                            ║      ",
		L"      ╠──────────┼───────────────┼──────────────╣      ",
		L"      ║                    │                              │                            ║      ",
		L"      ║         4          │                              │                            ║      ",
		L"      ║                    │                              │                            ║      ",
		L"      ╠──────────┴───────────────┴──────────────╣      ",
		L"      ║                              目前玩家:                                           ║      ",
		L"      ║                   存款                                     提款                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║          輸入存/提款金額(數字鍵):                                                ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ╚═════════════════════════════════════════╝      "
	};

	outputTextColor(Color::L_blue, Color::white);
	for (int i = 0; i < 33; i++)
	{
		moveCursor(0, i + 8);
		std::wcout << bank[i];
	}
	for (int i = 0; i < 4; i++)
	{
		moveCursor(42, 4*i + 16);
		if (i > Global::totalPlayer)
		{
			std::wcout << L"--";
		}
		else
		{
			std::wcout << Global::player[i].deposit;
		}
		moveCursor(75, 4 * i + 16);
		if (i > Global::totalPlayer)
		{
			std::wcout << L"--";
		}
		else
		{
			std::wcout << int(Global::player[i].deposit*(0.05));
		}
	}

	moveCursor(48, 31);
	std::wcout << player;

	outputTextColor(Color::white, Color::L_blue);
	if (choose == 0)
	{
		moveCursor(27, 32);
		std::wcout << L"存款";
	}
	else if (choose == 1)
	{
		moveCursor(69, 32);
		std::wcout << L"提款";
	}

	outputTextColor(Color::L_blue, Color::white);
	moveCursor(43, 34);
	std::wcout << money;

	moveCursor(0, 52);
	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}

//company=1,2,3 default=1
//choose:0,1 default=0
//money default=L"0"
void Display::printStock(int player, int company, int choose, std::wstring money)
{
	const std::wstring stock[33] = {
		L"      ╔═════════════════════════════════════════╗      ",
		L"      ║               ____      _______      ___        __                               ║      ",
		L"      ║             ∕             |       ∕   ∖    ∕  ∖     |  ∕                   ║      ",
		L"      ║             ╰---╮        |       |     |    |          |-<                     ║      ",
		L"      ║              ____∕        |       ∖___∕    ∖__∕     |  ∖                   ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║              價格                                     持有狀況                   ║      ",
		L"      ╠─────────────────┬───────────────────────╣      ",
		L"      ║             抬雞店               │           玩家1                張            ║      ",
		L"      ║                                  │           玩家2                張            ║      ",
		L"      ║                  元/張           │           玩家3                張            ║      ",
		L"      ║                   %              │           玩家4                張            ║      ",
		L"      ╠─────────────────┼───────────────────────╣      ",
		L"      ║             大力光               │           玩家1                張            ║      ",
		L"      ║                                  │           玩家2                張            ║      ",
		L"      ║                  元/張           │           玩家3                張            ║      ",
		L"      ║                   %              │           玩家4                張            ║      ",
		L"      ╠─────────────────┼───────────────────────╣      ",
		L"      ║              洪海                │           玩家1                張            ║      ",
		L"      ║                                  │           玩家2                張            ║      ",
		L"      ║                  元/張           │           玩家3                張            ║      ",
		L"      ║                   %              │           玩家4                張            ║      ",
		L"      ╠─────────────────┴───────────────────────╣      ",
		L"      ║                              目前玩家:                                           ║      ",
		L"      ║                    買                                       賣                   ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║           輸入買/賣張數(數字鍵):                                                 ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ╚═════════════════════════════════════════╝      "
	};

	//draw stock
	outputTextColor(Color::L_blue, Color::white);
	for (int i = 0; i < 33; i++)
	{
		moveCursor(0, i + 8);
		std::wcout << stock[i];
	}

	outputTextColor(Color::L_blue, Color::white);
	for (int i = 0; i < 3; i++)
	{
		moveCursor(18, 5*i + 18);
		std::wcout << Global::stockPrice[i];
		moveCursor(20, 5 * i + 19);
		int rate = Global::stockRate[i];
		if (rate > 0)
		{
			outputTextColor(Color::L_red, Color::white);
			std::wcout << L"▲";
		}
		else if (rate < 0)
		{
			outputTextColor(Color::L_green, Color::white);
			std::wcout << L"▼";
			rate = -rate;//abs
		}
		else
		{
			outputTextColor(Color::L_blue, Color::white);
			std::wcout << L"--";
		}
		moveCursor(24, 5 * i + 19);
		if (rate >= 10)
		{
			std::wcout << rate;
		}
		else
		{
			std::wcout << " " << rate;
		}

		outputTextColor(Color::L_blue, Color::white);
		for (int j = 0; j < 4; j++)
		{
			moveCursor(72, 5 * i + 16 + j);
			if (i > Global::totalPlayer)
			{
				std::wcout << L"--";
			}
			else
			{
				std::wcout << Global::player[j].stock[i];
			}
		}
	}
	//end draw

	outputTextColor(Color::white, Color::L_blue);
	if (company == 1)
	{
		moveCursor(21, 16);
		std::wcout << L"抬雞店";
	}
	else if (company == 2)
	{
		moveCursor(21, 21);
		std::wcout << L"大力光";
	}
	else if (company == 3)
	{
		moveCursor(22, 26);
		std::wcout << L"洪海";
	}

	outputTextColor(Color::L_blue, Color::white);
	moveCursor(48, 31);
	std::wcout << player;

	outputTextColor(Color::white, Color::L_blue);
	if (choose == 0)
	{
		moveCursor(28, 32);
		std::wcout << L"買";
	}
	else if (choose == 1)
	{
		moveCursor(69, 32);
		std::wcout << L"賣";
	}

	outputTextColor(Color::L_blue, Color::white);
	moveCursor(43, 34);
	std::wcout << money;

	moveCursor(0, 52);
	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}

//object=1,2,3,4,5 default=1
//selected default=false
//choose=0,1 default=0
void Display::printItem(int player, int object, bool selected, int choose)
{
	const std::wstring item[33] = {
		L"      ╔═════════════════════════════════════════╗      ",
		L"      ║                  _____      _____        ____       .      .                     ║      ",
		L"      ║                    |          |         |           |∖  ∕|                     ║      ",
		L"      ║                    |          |         |----       | ∖∕ |                     ║      ",
		L"      ║                  __|__        |         |____       |      |                     ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                                                                  ║      ",
		L"      ║                                  玩家:                                           ║      ",
		L"      ╠─────────────┬───────────────────────────╣      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          │        遙控骰子         x                            ║      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          ├───────────────────────────╣      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          │          路障           x                            ║      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          ├───────────────────────────╣      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          │         加速卡          x                            ║      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          ├───────────────────────────╣      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          │         烏龜卡          x                            ║      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          ├───────────────────────────╣      ",
		L"      ║                          │                                                      ║      ",
		L"      ║                          │         購地卡          x                            ║      ",
		L"      ║                          │                                                      ║      ",
		L"      ╚═════════════╧═══════════════════════════╝      ",
		L"                                                                                                  ",
		L"                                                                                                  ",
		L"                                                                                                  ",
		L"                                                                                                  ",
	};
	std::wstring tinyMenu[5] = {
		L" 使用 ",
		L"      ",
		L"      ",
		L"  是  ",
		L"  否  "
	};

	//draw item
	outputTextColor(Color::L_blue, Color::white);
	for (int i = 0; i < 33; i++)
	{
		moveCursor(0, i + 8);
		std::wcout << item[i];
	}

	for (int i = 0; i < 5; i++)
	{
		moveCursor(74, 4*i + 18);
		std::wcout << Global::player[player].item[i];
	}
	//end draw

	outputTextColor(Color::L_blue, Color::white);
	moveCursor(48, 8 + 7);
	std::wcout << player+1;

	outputTextColor(Color::white, Color::L_blue);
	if (object == 1)
	{
		moveCursor(44, 8 + 10);
		std::wcout << L"遙控骰子";
	}
	else if (object == 2)
	{
		moveCursor(44, 8 + 14);
		std::wcout << L"  路障  ";
	}
	else if (object == 3)
	{
		moveCursor(44, 8 + 18);
		std::wcout << L" 加速卡 ";
	}
	else if (object == 4)
	{
		moveCursor(44, 8 + 22);
		std::wcout << L" 烏龜卡 ";
	}
	else if (object == 5)
	{
		moveCursor(44, 8 + 26);
		std::wcout << L" 購地卡 ";
	}

	if (selected)
	{
		outputTextColor(Color::L_blue, Color::white);
		for (int i = 0; i < 5; i++)
		{
			moveCursor(17, 24 + i);
			std::wcout << tinyMenu[i];
		}

		outputTextColor(Color::white, Color::L_blue);
		moveCursor(17, 27 + choose);
		std::wcout << tinyMenu[3 + choose];
	}

	moveCursor(0, 52);
	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}

//mode 1
void Display::printMessage(int round, int player)
{
	std::wstring info[4] = {
		L"剩餘回合: ",
		L"當前玩家: ",
		L"",
		L"按ENTER擲骰..."
	};

	outputTextColor(Color::black, Color::L_cyan);
	for (int i = 0; i < 4; i++)
	{
		moveCursor(41, i + 44);
		std::wcout << info[i];
	}

	moveCursor(51, 0 + 44);
	std::wcout << round;
	moveCursor(51, 1 + 44);
	std::wcout << player;

	moveCursor(0, 52);
	//initialize
	outputTextColor(Color::D_white, Color::black);
	cursor.X = 0;
	cursor.Y = 0;
}

//building default=L""
//owner default=-1(no owner)
//dollar default=0
//payStatus=0(unsure),1(true),2(false),3(no money),4(level max) default=0
void Display::printMessage(int throwPoint, int player, bool stopped,
	std::wstring building, int owner, int dollar, int payStatus)
{
	outputTextColor(Color::black, Color::L_cyan);
	moveCursor(41, 0 + 44);
	std::wcout << L"投到 " << throwPoint;

	if (stopped)
	{
		moveCursor(41, 1 + 44);
		std::wcout << L"玩家 " << player << L"到了" << building;

		moveCursor(41, 2 + 44);
		if (owner == -1)
		{
			//no owner
			std::wcout << L"此為無主地，要花費" << dollar << L"元購買嗎? ";
		}
		else if (owner == player)
		{
			//self
			std::wcout << L"此為你的土地，要花費" << dollar << L"元升級嗎? ";
		}
		else
		{
			//others
			std::wcout << L"此為玩家" << owner << L"的土地，需付款 " << dollar << L"元";
		}

		if (payStatus == 1)
		{
			moveCursor(41, 3 + 44);
			std::wcout << L"付款成功";
			moveCursor(41, 4 + 44);
			std::wcout << L"按ENTER結束回合...";
		}
		else if (payStatus == 2)
		{
			moveCursor(41, 3 + 44);
			std::wcout << L"選擇不執行動作";
			moveCursor(41, 4 + 44);
			std::wcout << L"按ENTER結束回合...";
		}
		else if (payStatus == 3)
		{
			moveCursor(41, 3 + 44);
			std::wcout << L"現金不足，無法支付";
			moveCursor(41, 4 + 44);
			std::wcout << L"按ENTER結束回合...";
		}
		else if (payStatus == 4)
		{
			moveCursor(41, 3 + 44);
			std::wcout << L"等級已滿，無法升級";
			moveCursor(41, 4 + 44);
			std::wcout << L"按ENTER結束回合...";
		}
	}
	else
	{
		moveCursor(41, 1 + 44);
		std::wcout << L"移動中...";
	}
}

//object=1,2,3,4,5
//playerStatus=0,1(x2),2(/2) default=0
//select default=1
//money default=0
//paymentStatus=0,1,2 default=0
void Display::printMessage(int round, int player, int object, int playerStatus,
	int select, int money, int paymentStatus)
{
	outputTextColor(Color::black, Color::L_cyan);
	moveCursor(41, 0 + 44);
	std::wcout << L"當前回合: " << round;
	moveCursor(41, 1 + 44);
	std::wcout << L"當前玩家: " << player;
	moveCursor(41, 2 + 44);
	std::wcout << L"使用了道具 ";

	if (object == 1)//selection dice
	{
		std::wcout << L"遙控骰子";

		moveCursor(41, 3 + 44);
		std::wcout << L"<-   ->";

		moveCursor(41, 4 + 44);
		int points[12] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
		if (playerStatus == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				if (i == select - 1)
				{
					outputTextColor(Color::white, Color::L_blue);
					std::wcout << points[i];
					outputTextColor(Color::black, Color::L_cyan);
					std::wcout << L" ";
				}
				else
				{
					std::wcout << points[i] << L" ";
				}
			}
		}
		else if (playerStatus == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				if (i == select - 1)
				{
					outputTextColor(Color::white, Color::L_blue);
					std::wcout << points[i];
					outputTextColor(Color::black, Color::L_cyan);
					std::wcout << L" ";
				}
				else
				{
					std::wcout << points[i] << L" ";
				}
			}
		}
		else if (playerStatus == 2)
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == select - 1)
				{
					outputTextColor(Color::white, Color::L_blue);
					std::wcout << points[i];
					outputTextColor(Color::black, Color::L_cyan);
					std::wcout << L" ";
				}
				else
				{
					std::wcout << points[i] << L" ";
				}
			}
		}
	}
	else if (object == 2)//barrier
	{
		std::wcout << L"路障";
		moveCursor(41, 3 + 44);
		std::wcout << L"已在此處放置路障";
		moveCursor(41, 4 + 44);
		std::wcout << L"按ENTER繼續...";
	}
	else if (object == 3)//faster
	{
		std::wcout << L"加速卡";
		moveCursor(41, 3 + 44);
		std::wcout << L"按ENTER繼續...";
	}
	else if (object == 4)//turtle
	{
		std::wcout << L"烏龜卡";
		moveCursor(41, 3 + 44);
		std::wcout << L"按ENTER繼續...";
	}
	else if (object == 5)//buy house
	{
		std::wcout << L"購地卡";
		moveCursor(41, 3 + 44);
		if (paymentStatus == 0)
		{
			std::wcout << L"購買成功，已付款" << money << L"元";
		}
		else if (paymentStatus == 1)
		{
			std::wcout << L"購買失敗，餘額不足";
		}
		else if (paymentStatus == 2)
		{
			std::wcout << L"購買失敗，非可購入地產";
		}
		moveCursor(41, 4 + 44);
		std::wcout << L"按ENTER繼續...";
	}
}

//eventCode=0(opportunity),1(destiny)
void Display::printMessage(int throwPoint, int player, int eventCode, std::wstring eventMsg)
{
	outputTextColor(Color::black, Color::L_cyan);
	moveCursor(41, 0 + 44);
	std::wcout << L"投到 " << throwPoint;

	moveCursor(41, 1 + 44);
	std::wcout << L"玩家 " << player << L"到了";
	if (eventCode == 0)
	{
		std::wcout << L"機會";
	}
	else if (eventCode == 1)
	{
		std::wcout << L"命運";
	}

	moveCursor(41, 2 + 44);
	std::wcout << L"發生事件: " << eventMsg;
	moveCursor(41, 3 + 44);
	std::wcout << L"按ENTER結束回合...";
}

void Display::printWinMsg(int player)
{
	outputTextColor(Color::black, Color::L_cyan);
	moveCursor(41, 0 + 44);
	std::wcout << L"玩家 " << player << L"獲勝";
}
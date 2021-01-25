#include<iomanip>
#include<io.h>
#include<fcntl.h>
#include<locale>
#include<codecvt>
#include "File.h"
#include"GlobalVariable.h"

std::wfstream File::f;

File::File()
{

}


File::~File()
{
}

bool File::readFile(std::string pos)
{
	f.open(pos, std::ios::in);

	if (f.fail())
	{
		f.close();
		return false;
	}
	else
	{
		std::wstring temp;

		f.imbue(std::locale(f.getloc(), "", LC_CTYPE));

		f >> Global::mapName >> Global::remainRound >> Global::totalPlayer;
		for (int i = 0; i < 28; i++)
		{
			Global::house[i] = House();
			f >> Global::house[i].location >> Global::house[i].name >> Global::house[i].type;
			if (Global::house[i].type == 1)
			{
				f >> Global::house[i].price;
				for (int j = 0; j < 4; j++)
				{
					f >> Global::house[i].fee[j];
				}
			}
		}
		Global::player.clear();
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			Player p;
			Global::player.push_back(p);
		}

		f >> temp >> Global::currentPlayer;

		for (int i = 0; i < Global::totalPlayer; i++)
		{
			f >> temp >> Global::player[i].position >> Global::player[i].cash;

			if (Global::player[i].cash == 0)
			{
				Global::player[i].survive = false;
			}

			int estate, level;
			while (f.peek() != '\n')
			{
				f >> estate >> level;
				Global::player[i].estate.push_back(estate);
				Global::house[estate].owner = i;
				Global::house[estate].level = level;
			}
		}

		while (!f.eof())
		{
			f >> temp;//bank
			if (temp == L"bank")
			{
				for (int i = 0; i < Global::totalPlayer; i++)
				{
					f >> temp >> Global::player[i].deposit;

					if (!Global::player[i].survive && Global::player[i].deposit != 0)
					{
						Global::player[i].survive = true;
					}
				}
			}
			else if (temp == L"stock")
			{
				for (int i = 0; i < Global::totalPlayer; i++)
				{
					f >> temp;
					for (int j = 0; j < 3; j++)
					{
						f >> Global::player[i].stock[j];
					}
				}
			}
			else if (temp == L"item")
			{
				for (int i = 0; i < Global::totalPlayer; i++)
				{
					f >> temp;
					for (int j = 0; j < 5; j++)
					{
						f >> Global::player[i].item[j];
					}
				}
			}
		}

		f.close();

		for (int i = 0; i < Global::totalPlayer; i++)
		{
			if (!Global::player[i].survive)
			{
				Global::player[i].setDeath();
			}
		}
		return true;
	}
}

bool File::writeFile(std::string pos)
{
	f.open(pos, std::ios::out);
	if (f.fail())
	{
		f.close();
		return false;
	}
	else
	{
		f << Global::mapName << " " << Global::remainRound << " " << Global::totalPlayer << std::endl;
		for (int i = 0; i < 28; i++)
		{
			f << std::setw(2) << std::setfill(L'0') << i;
			f << L" " << Global::house[i].name << " " << Global::house[i].type;
			if (Global::house[i].type == 1)
			{
				f << L" " << Global::house[i].price;
				for (int j = 0; j < 4; j++)
				{
					f << L" " << Global::house[i].fee[j];
				}
			}
			f << std::endl;
		}

		f << L"playerstate " << Global::currentPlayer << std::endl;
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			f << i;
			f << L" ";
			f << std::setw(2) << std::setfill(L'0') << Global::player[i].position;
			f << L" ";
			f << Global::player[i].cash;

			for (auto ite = Global::player[i].estate.begin(); ite != Global::player[i].estate.end(); ite++)
			{
				f << L" " << *ite << L" " << Global::house[*ite].level;
			}

			f << std::endl;
		}

		f << L"bank" << std::endl;
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			f << i << " " << Global::player[i].deposit << std::endl;
		}

		f << L"stock" << std::endl;
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			f << i;
			for (int j = 0; j < 3; j++)
			{
				f << L" " << Global::player[i].stock[j];
			}
			f << std::endl;
		}
		f << L"item" << std::endl;
		for (int i = 0; i < Global::totalPlayer; i++)
		{
			f << i;
			for (int j = 0; j < 5; j++)
			{
				f << L" " << Global::player[i].item[j];
			}
			f << std::endl;
		}

		f.close();
		return true;
	}
}
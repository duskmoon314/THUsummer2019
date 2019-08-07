#include "gameIO.h"

void game_io::run()
{
	system("cls");
	index();
	auto input = 0;
	while (true)
	{
		std::cin >> input;
		if (input == 1)
		{
			play();
		}
		if (input == 2)
		{
			return;
		}
	}
}

void game_io::index()
{
	system("cls");
	std::cout << "**********##########**********\n"
		<< "      一个简易的3D五子棋\n\n"
		<< "       Author: Duskmoon\n"
		<< "          作者： 暮月\n"
		<< "**********##########**********\n\n";

	std::cout << "输入1开始游戏，输入2退出\n";
}

void game_io::play()
{
	auto color = 0;
	while (true)
	{
		system("cls");
		std::cout << *this;
		std::string str = color % 2 == 0 ? "黑方" : "白方";
		std::cout << "现在是" << str << "落子\n";
		int x, y, z;
		std::cout << "请输入直角坐标 1-9，用空格隔开，回车结束\n";
		std::cin >> x >> y >> z;
		auto color_here = (color % 2) == 0 ? black : white;
		(*this).set_piece(x, y, z, color_here);
		auto check = (*this).check_win(x, y, z);
		if (check != none)
		{
			std::cout << "Game Over\nWinner: ";
			if (check == black)
			{
				std::cout << "BLACK\n";
			}
			else
			{
				std::cout << "WHITE\n";
			}
			auto choice = 0;
			std::cout << "输入1返回主界面\n";
			while (true)
			{
				std::cin >> choice;
				if(choice == 1)
				{
					return;
				}
			}
		}
		++color;
	}
}

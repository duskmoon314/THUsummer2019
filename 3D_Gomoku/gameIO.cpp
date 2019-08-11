#include "gameIO.h"

void game_io::run()
{
	system("cls");
	
	while (true)
	{
		index();
		auto input = 0;
		std::cin >> input;
		if (input == 1)
		{
			play();
		}
		else if(input == 2)
		{
			load();
			play();
		}
		else if (input == 3)
		{
			return;
		}
		else {
			std::cout << "输入错误\n";
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

	std::cout << "输入1开始游戏，输入2载入游戏，输入3退出\n";
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
		std::cout << "已经落子共" << history.size() << "次\n"
			<< "若要悔棋请键入1，继续下棋键入2，存储游戏键入3：\n";
		auto input = 0;
		while (true)
		{
			std::cin >> input;
			if (input == 1)
			{
				std::cout << "请输入一个不大于" << history.size() << "的数字，将返回至输入步数之前\n";
				auto times = 0;
				while (true)
				{
					std::cin >> times;
					if (times > history.size())
					{
						std::cout << "输入错误\n";
					}
					else
					{
						history.history_pop(times, *this);
						break;
					}
				}
				break;
			}
			else if (input == 2)
			{
				int x, y, z;
				std::cout << "请输入直角坐标 1-9，用空格隔开，回车结束\n";
				std::cin >> x >> y >> z;

				point point(x, y, z);
				history.push(point);

				auto color_here = color % 2 == 0 ? black : white;
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
						if (choice == 1)
						{
							return;
						}
					}
				}
				++color;
				break;
			}
			else if(input ==3)
			{
				save();
				std::cout << "存储完毕，键入1返回主菜单\n";
				std::cin.ignore();
				auto input2 = 0;
				while(true)
				{
					std::cin >> input2;
					if(input2 == 1)
					{
						return;
					}
					std::cout << "输入错误\n";
				}
			}
			else
			{
				std::cout << "输入错误\n";
			}
		}
	}
}

void game_io::load()
{
	history.pop(history.size());
	system("cls");
	std::cout << "**********##########**********\n"
		<< "      一个简易的3D五子棋\n\n"
		<< "       Author: Duskmoon\n"
		<< "          作者： 暮月\n"
		<< "**********##########**********\n\n";

	std::cout << "请输入存储的游戏文件完整路径：\n";
	std::string file_name;
	std::cin >> file_name;
	std::fstream fs;
	fs.open(file_name.c_str(), std::ios::in);
	auto color = 0;
	while (fs.peek() != EOF) {
		int x, y, z;
		fs >> x >> y >> z;
		point point(x, y, z);
		history.push(point);

		auto color_here = color % 2 == 0 ? black : white;
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
				if (choice == 1)
				{
					return;
				}
			}
		}
		++color;
		fs.get();
	}
}

void game_io::save()
{
	std::cout << "请输入要存储的游戏文件完整路径：\n";
	std::string file_name;
	std::cin >> file_name;
	std::fstream fs;
	fs.open(file_name.c_str(), std::ios::out);
	history.write(fs);
	fs.close();
}

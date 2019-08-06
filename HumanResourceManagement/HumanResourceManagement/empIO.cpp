#include "empIO.h"
#include <utility>

fstream fs;

string enum_position[4] = {"Manager", "Salesman", "Technician", "Sales_manager"};

/**
 * \brief 
 * \param file_name 
 */
auto run(std::string file_name) -> void
{
	while (true)
	{
		index(file_name);
		auto input = 0;
		std::cin >> input;
		switch (input)
		{
			//浏览功能
		case 1:
			explore(file_name);
			break;

			//修改功能
		case 2:
			modify(file_name);
			break;

			//查询功能
		case 3:
			search(file_name);
			break;

			//保存新文件
		case 4:
			save(file_name);
			break;

			//选择文件
		case 5:
			change_file(file_name);
			break;

			//退出
		case 6:
			//system("exit");
			return;

		default:
			std::cout << "输入错误\n";
			break;
		}
	}
}

/**
 * \brief 
 * \param file_name 
 */
auto index(std::string& file_name) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n";

	std::cout << "    This is a simple human resource management\n"
		<< "            这是一个简易的人事管理系统\n"
		<< "\n                 coded by duskmoon\n"
		<< "                    由暮月编写\n";

	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\n                     HomePage                     \n"
		<< "                     1. 浏览\n"
		<< "                     2. 修改\n"
		<< "                     3. 查询\n"
		<< "                     4. 保存至新文件\n"
		<< "                     5. 选择文件\n"
		<< "                     6. 退出\n";

	std::cout << "             请输入序号以执行相应操作\n"
		<< "             当前操作文件：" << file_name << std::endl;

	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

/**
 * \brief 
 * \param file_name 
 */
auto explore(const std::string& file_name) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     浏览模式\n";

	try
	{
		fs.open(file_name.c_str(), std::ios::in);
		if (fs.is_open())
		{
			char content[200];
			auto is_empty = true;
			while (fs.peek() != EOF)
			{
				is_empty = false;
				fs.getline(content, 200);
				std::cout << content << '\n';
			}
			fs.close();
			if (is_empty)
			{
				cout << "空文件，请更换操作文件或使用修改模式添加对象\n";
			}
		}
		else
		{
			throw open_error(file_name);
		}
	}
	catch (open_error& o)
	{
		std::cerr << o.what() << '\n';
	}

	std::cout << "显示完毕\n输入1返回主界面：";

	auto input = 0;
	while (true)
	{
		try
		{
			std::cin >> input;
			if (input != 1)
			{
				throw input_error();
			}
			return;
		}
		catch (input_error& i)
		{
			std::cerr << i.what() << '\n';
		}
	}
}

/**
 * \brief 
 * \param file_name 
 */
auto modify(const std::string& file_name) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     修改模式\n";

	std::cout << "                     1. 添加\n"
		<< "                     2. 删除\n"
		<< "                     3. 修改\n"
		<< "                     4. 返回\n";

	vector<employee*> employees;
	load(file_name, employees);

	auto input = 0;
	while (true)
	{
		try
		{
			std::cin >> input;
			switch (input)
			{
			case 1:
				{
					mod_add(employees);
					try
					{
						fs.open(file_name.c_str(), std::ios::out);
						if (fs.is_open())
						{
							for (auto& it : employees)
							{
								it->write(fs);
								fs << '\n';
							}
							fs.close();
						}
						else
						{
							throw open_error(file_name);
						}
					}
					catch (open_error& o)
					{
						std::cerr << o.what() << '\n';
					}
					return;
				}
			case 2:
				{
					mod_delete(employees);
					try
					{
						fs.open(file_name.c_str(), std::ios::out);
						if (fs.is_open())
						{
							for (auto& it : employees)
							{
								it->write(fs);
								fs << '\n';
							}
							fs.close();
						}
						else
						{
							throw open_error(file_name);
						}
					}
					catch (open_error& o)
					{
						std::cerr << o.what() << '\n';
					}
					return;
				}
			case 3:
				{
					mod_modify(employees);
					try
					{
						fs.open(file_name.c_str(), std::ios::out);
						if (fs.is_open())
						{
							for (auto& it : employees)
							{
								it->write(fs);
								fs << '\n';
							}
							fs.close();
						}
						else
						{
							throw open_error(file_name);
						}
					}
					catch (open_error& o)
					{
						std::cerr << o.what() << '\n';
					}
					return;
				}
			case 4:
				{
					return;
				}
			default:
				{
					throw input_error();
				}
			}
		}
		catch (input_error& i)
		{
			std::cerr << i.what() << '\n';
		}
	}
}

auto search(const std::string& file_name) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     查询模式\n";

	vector<employee*> employees;
	load(file_name, employees);

	std::cout << "\n请输入要查询的id或姓名：\n";
	std::string target;
	std::cin >> target;
	auto find = false;
	try
	{
		if (isdigit(target[0]))
		{
			for (auto& it : employees)
			{
				if (it->get_id() == stoi(target))
				{
					find = true;
					it->print();
				}
			}
		}
		else
		{
			for (auto& it : employees)
			{
				if (it->get_name() == target)
				{
					find = true;
					cout << it;
				}
			}
		}
		if (!find)
		{
			throw search_error();
		}
	}
	catch (search_error& s)
	{
		std::cerr << s.what() << '\n';
	}
}

auto change_file(std::string file_name) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     选择文件\n";

	std::cout << "      当前操作文件为：" << file_name << '\n'
		<< "              确认更改？\n"
		<< "          1 (YES)  2 (NO)\n";

	auto input = 0;
	while (true)
	{
		try
		{
			std::cin >> input;
			if (input == 1)
			{
				std::cout << "请输入文件名，包含完整路径与后缀（建议使用txt），回车结束\n";
				char temp[300];
				std::cin.ignore();
				std::cin.getline(temp, 300);
				file_name = temp;
				return;
			}
			if (input == 2)
			{
				return;
			}
			throw input_error();
		}
		catch (input_error& i)
		{
			std::cerr << i.what() << '\n';
		}
	}
}

auto save(std::string file_name) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                   保存至新文件\n";

	std::cout << " 当前操作文件：" << file_name << std::endl;
	std::cout << " 请输入新文件路径\n";
	std::string new_file;
	std::cin >> new_file;
	std::ifstream in;
	std::ofstream out;
	try
	{
		in.open(file_name, std::ios::in);
		out.open(new_file, std::ios::out);
		if (!in.is_open())
		{
			throw open_error(file_name);
		}
		else if (!out.is_open())
		{
			throw open_error(new_file);
		}
		else
		{
			char temp[1000];
			while (in.peek() != EOF)
			{
				in.getline(temp, 1000);
				out << temp << std::endl;
			}
			in.close();
			out.close();
		}
	}
	catch (const open_error& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "保存完毕，是否需要切换操纵新文件？\n1(YES) 2(NO)\n";
	auto choice = 0;
	try
	{
		while (true)
		{
			std::cin >> choice;
			if (choice == 1)
			{
				file_name = new_file;
				return;
			}
			if (choice == 2)
			{
				return;
			}
			throw input_error();
		}
	}
	catch (input_error& i)
	{
		std::cerr << i.what() << '\n';
	}
}

auto load(const std::string& file_name, vector<employee*>& employees) -> void
{
	try
	{
		fs.open(file_name.c_str(), std::ios::in);
		if (fs.is_open())
		{
			auto is_empty = true;
			auto count = 0;
			string position;
			while (fs.peek() != EOF)
			{
				++count;
				is_empty = false;

				fs >> position;
				if (!strcmp(position.c_str(), "Manager"))
				{
					int id, grade;
					string name;
					double monthly_salary;
					fs >> id >> name >> grade >> monthly_salary;
					employee* pemp = new manager(id, grade, name);
					employees.push_back(pemp);
				}
				else if (!strcmp(position.c_str(), "Technician"))
				{
					int id, grade, work_hours_per_month;
					double pay_per_hour, monthly_salary;
					string name;
					fs >> id >> name >> grade >> monthly_salary >> work_hours_per_month >> pay_per_hour;
					employee* pemp = new technician(id, grade, name, work_hours_per_month);
					employees.push_back(pemp);
				}
				else if (!strcmp(position.c_str(), "Salesman"))
				{
					int id, grade;
					double sales_value, commission_rate, monthly_salary;
					string name;
					fs >> id >> name >> grade >> monthly_salary >> commission_rate >> sales_value;
					employee* pemp = new salesman(id, grade, name, sales_value);
					employees.push_back(pemp);
				}
				else if (!strcmp(position.c_str(), "Sales_manager"))
				{
					int id, grade;
					double total_sales_value, commission_rate, monthly_salary;
					string name;
					fs >> id >> name >> grade >> monthly_salary >> commission_rate >> total_sales_value;
					sales_manager sales_manager(id, grade, name, total_sales_value);
					char c;
					while (cin.get(c) && c != ']')
					{
						int i;
						cin >> i;
						if (i <= 0)break;
						// 如果sales_manager.subordinate_salesman为空，即读入为[]，这样操作会带来问题
						// 测试得到vs会将其转为0，故这里尝试使用一个if安全地解决问题
						sales_manager.subordinate_salesman.push_back(i);
					}
				}
				else
				{
					// 不合规范的文件
				}
				if(count == 1)
				{
					employees[0]->initial();
				}
				fs.get();
				if (fs.peek() == '\n')break;
			}
			fs.close();
			if (is_empty)
			{
				cout << "空文件，请更换操作文件或使用修改模式添加对象\n";
			}
		}
		else
		{
			throw open_error(file_name);
		}
	}
	catch (open_error& o)
	{
		std::cerr << o.what() << '\n';
	}
}

auto mod_add(vector<employee*>& employees) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     修改模式\n"
		<< "                       添加\n";

	std::cout << "  请选择添加成员的职位：\n"
		<< "  1. Manager\n  2. Technician\n  3. Salesman\n  4. Sales_manager\n";
	try
	{
		auto input = 0;
		std::cin >> input;
		while (true)
		{
			switch (input)
			{
			case 1:
				{
					int grade;
					string name;
					std::cout << "\n请输入姓名: ";
					std::cin >> name;
					std::cout << "\n请输入等级: ";
					std::cin >> grade;
					employee* pemp = new manager(grade, name);
					employees.push_back(pemp);
					return;
				}
			case 2:
				{
					int grade, work_hours_per_month;
					string name;
					std::cout << "\n请输入姓名: ";
					std::cin >> name;
					std::cout << "\n请依次输入等级、每月工作时长: ";
					std::cin >> grade >> work_hours_per_month;
					employee* pemp = new technician(grade, name, work_hours_per_month);
					employees.push_back(pemp);
					return;
				}
			case 3:
				{
					int grade;
					double sales_value;
					string name;
					std::cout << "\n请输入姓名: ";
					std::cin >> name;
					std::cout << "\n请依次输入等级、销售额: ";
					std::cin >> grade >> sales_value;
					employee* pemp = new salesman(grade, name, sales_value);
					employees.push_back(pemp);
					return;
				}
			case 4:
				{
					int grade;
					double total_sales_value;
					string name;
					std::cout << "\n请输入姓名: ";
					std::cin >> name;
					std::cout << "\n请依次输入等级、总销售额: ";
					std::cin >> grade >> total_sales_value;
					sales_manager sales_manager(grade, name, total_sales_value);
					std::cout << "\n请输入销售经理手下销售人员的id（正整数），以空格或回车隔开，任意字符结尾\n";
					unsigned int id;
					while (cin >> id)
					{
						sales_manager.subordinate_salesman.push_back(id);
					}
					return;
				}
			default:
				{
					throw input_error();
				}
			}
		}
	}
	catch (input_error& i)
	{
		std::cerr << i.what() << '\n';
	}
}

auto mod_delete(vector<employee*>& employees) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     修改模式\n"
		<< "                       删除";

	std::cout << "\n请输入要删除的id或姓名：\n";
	std::string target;
	std::cin >> target;
	auto find = false;
	try
	{
		if (isdigit(target[0]))
		{
			for (auto& it : employees)
			{
				if (it->get_id() == stoi(target))
				{
					find = true;
					it->print();
					std::cout << "确定删除吗？\n1 (YES)  2 (NO)\n";
					auto input = 0;
					try
					{
						while (true)
						{
							cin >> input;
							if (input == 1)
							{
								employees.erase(remove(employees.begin(), employees.end(), it), employees.end());
								return;
							}
							if (input == 2)
							{
								return;
							}
							throw input_error();
						}
					}
					catch (input_error& i)
					{
						std::cerr << i.what() << '\n';
					}
				}
			}
		}
		else
		{
			for (auto& it : employees)
			{
				if (it->get_name() == target)
				{
					find = true;
					std::cout << it;
					std::cout << "确定删除吗？\n1 (YES)  2 (NO)\n";
					auto input = 0;
					try
					{
						while (true)
						{
							cin >> input;
							if (input == 1)
							{
								employees.erase(remove(employees.begin(), employees.end(), it), employees.end());
								return;
							}
							if (input == 2)
							{
								return;
							}
							throw input_error();
						}
					}
					catch (input_error& i)
					{
						std::cerr << i.what() << '\n';
					}
				}
			}
		}
		if (!find)
		{
			throw search_error();
		}
	}
	catch (search_error& s)
	{
		std::cerr << s.what() << '\n';
	}
}

auto mod_modify(vector<employee*>& employees) -> void
{
	system("cls");
	std::cout << "##########**********##########**********##########\n"
		<< "                   人事管理系统                   \n"
		<< "##########**********##########**********##########\n"
		<< "                     修改模式\n"
		<< "                       修改";

	std::cout << "\n请输入要修改的id或姓名：\n";
	std::string target;
	std::cin >> target;
	auto find = false;
	try
	{
		if (isdigit(target[0]))
		{
			for (auto& it : employees)
			{
				if (it->get_id() == stoi(target))
				{
					find = true;
					it->print();
					std::cout << "确定修改吗？\n1 (YES)  2 (NO)\n";
					auto input = 0;
					try
					{
						while (true)
						{
							std::cin >> input;
							if (input == 1)
							{
								std::cout << "1 改名  2 改变等级  3其他\n";
								//Manager
								if (it->get_position() == enum_position[0])
								{
									auto input2 = 0;
									try
									{
										while (true)
										{
											std::cout << "1 改名  2 改变等级  3 返回\n";
											std::cin >> input2;
											if (input2 == 1)
											{
												std::cout << "请输入姓名: \n";
												string new_name;
												std::cin >> new_name;
												it->set_name(new_name);
												//return;
											}
											else if (input2 == 2)
											{
												std::cout << "请输入等级: \n";
												auto grade = 0;
												std::cin >> grade;
												it->promote(grade);
												it->pay();
											}
											else if (input2 == 3)
											{
												return;
											}
											else
											{
												throw input_error();
											}
										}
									}
									catch (input_error& i)
									{
										std::cerr << i.what() << '\n';
									}
								}
								if (it->get_position() == enum_position[1])
								{
									auto input2 = 0;
									try
									{
										while (true)
										{
											std::cout << "1 改名  2 改变等级  3 改变销售额  4 返回\n";
											std::cin >> input2;
											if (input2 == 1)
											{
												std::cout << "请输入姓名: \n";
												string new_name;
												std::cin >> new_name;
												it->set_name(new_name);
												//return;
											}
											else if (input2 == 2)
											{
												std::cout << "请输入等级: \n";
												auto grade = 0;
												std::cin >> grade;
												it->promote(grade);
												it->pay();
											}
											else if (input2 == 3)
											{
												std::cout << "请输入销售额: \n";
												auto sales_value = 0.0;
												std::cin >> sales_value;
												it->set_sales_value(sales_value);
												it->pay();
											}
											else if (input2 == 4)
											{
												return;
											}
											else
											{
												throw input_error();
											}
										}
									}
									catch (input_error& i)
									{
										std::cerr << i.what() << '\n';
									}
								}
								if (it->get_position() == enum_position[3])
								{
									auto input2 = 0;
									try
									{
										while (true)
										{
											std::cout << "1 改名  2 改变等级  3 改变工作时长  4 返回\n";
											std::cin >> input2;
											if (input2 == 1)
											{
												std::cout << "请输入姓名: \n";
												string new_name;
												std::cin >> new_name;
												it->set_name(new_name);
												//return;
											}
											else if (input2 == 2)
											{
												std::cout << "请输入等级: \n";
												auto grade = 0;
												std::cin >> grade;
												it->promote(grade);
												it->pay();
											}
											else if (input2 == 3)
											{
												std::cout << "请输入月工作时长: \n";
												auto work_hours_per_month = 0;
												std::cin >> work_hours_per_month;
												it->set_work_hours_per_month(work_hours_per_month);
												it->pay();
											}
											else if (input2 == 4)
											{
												return;
											}
											else
											{
												throw input_error();
											}
										}
									}
									catch (input_error& i)
									{
										std::cerr << i.what() << '\n';
									}
								}
								if (it->get_position() == enum_position[0])
								{
									auto input2 = 0;
									try
									{
										while (true)
										{
											std::cout << "1 改名  2 改变等级  3 返回\n";
											std::cin >> input2;
											if (input2 == 1)
											{
												std::cout << "请输入姓名: \n";
												string new_name;
												std::cin >> new_name;
												it->set_name(new_name);
												//return;
											}
											else if (input2 == 2)
											{
												std::cout << "请输入等级: \n";
												auto grade = 0;
												std::cin >> grade;
												it->promote(grade);
												it->pay();
											}
											else if (input2 == 3)
											{
												return;
											}
											else
											{
												throw input_error();
											}
										}
									}
									catch (input_error& i)
									{
										std::cerr << i.what() << '\n';
									}
								}
							}
							if (input == 2)
							{
								return;
							}
							throw input_error();
						}
					}
					catch (input_error& i)
					{
						std::cerr << i.what() << '\n';
					}
				}
			}
		}
		else
		{
		for (auto& it : employees)
		{
			if (it->get_id() == stoi(target))
			{
				find = true;
				it->print();
				std::cout << "确定修改吗？\n1 (YES)  2 (NO)\n";
				auto input = 0;
				try
				{
					while (true)
					{
						std::cin >> input;
						if (input == 1)
						{
							//Manager
							if (it->get_position() == enum_position[0])
							{
								auto input2 = 0;
								try
								{
									while (true)
									{
										std::cout << "1 改名  2 改变等级  3 返回\n";
										std::cin >> input2;
										if (input2 == 1)
										{
											std::cout << "请输入姓名: \n";
											string new_name;
											std::cin >> new_name;
											it->set_name(new_name);
											//return;
										}
										else if (input2 == 2)
										{
											std::cout << "请输入等级: \n";
											auto grade = 0;
											std::cin >> grade;
											it->promote(grade);
											it->pay();
										}
										else if (input2 == 3)
										{
											return;
										}
										else
										{
											throw input_error();
										}
									}
								}
								catch (input_error& i)
								{
									std::cerr << i.what() << '\n';
								}
							}
							if (it->get_position() == enum_position[1])
							{
								auto input2 = 0;
								try
								{
									while (true)
									{
										std::cout << "1 改名  2 改变等级  3 改变销售额  4 返回\n";
										std::cin >> input2;
										if (input2 == 1)
										{
											std::cout << "请输入姓名: \n";
											string new_name;
											std::cin >> new_name;
											it->set_name(new_name);
											//return;
										}
										else if (input2 == 2)
										{
											std::cout << "请输入等级: \n";
											auto grade = 0;
											std::cin >> grade;
											it->promote(grade);
											it->pay();
										}
										else if (input2 == 3)
										{
											std::cout << "请输入销售额: \n";
											auto sales_value = 0.0;
											std::cin >> sales_value;
											it->set_sales_value(sales_value);
											it->pay();
										}
										else if (input2 == 4)
										{
											return;
										}
										else
										{
											throw input_error();
										}
									}
								}
								catch (input_error& i)
								{
									std::cerr << i.what() << '\n';
								}
							}
							if (it->get_position() == enum_position[3])
							{
								auto input2 = 0;
								try
								{
									while (true)
									{
										std::cout << "1 改名  2 改变等级  3 改变工作时长  4 返回\n";
										std::cin >> input2;
										if (input2 == 1)
										{
											std::cout << "请输入姓名: \n";
											string new_name;
											std::cin >> new_name;
											it->set_name(new_name);
											//return;
										}
										else if (input2 == 2)
										{
											std::cout << "请输入等级: \n";
											auto grade = 0;
											std::cin >> grade;
											it->promote(grade);
											it->pay();
										}
										else if (input2 == 3)
										{
											std::cout << "请输入月工作时长: \n";
											auto work_hours_per_month = 0;
											std::cin >> work_hours_per_month;
											it->set_work_hours_per_month(work_hours_per_month);
											it->pay();
										}
										else if (input2 == 4)
										{
											return;
										}
										else
										{
											throw input_error();
										}
									}
								}
								catch (input_error& i)
								{
									std::cerr << i.what() << '\n';
								}
							}
							if (it->get_position() == enum_position[0])
							{
								auto input2 = 0;
								try
								{
									while (true)
									{
										std::cout << "1 改名  2 改变等级  3 返回\n";
										std::cin >> input2;
										if (input2 == 1)
										{
											std::cout << "请输入姓名: \n";
											string new_name;
											std::cin >> new_name;
											it->set_name(new_name);
											//return;
										}
										else if (input2 == 2)
										{
											std::cout << "请输入等级: \n";
											auto grade = 0;
											std::cin >> grade;
											it->promote(grade);
											it->pay();
										}
										else if (input2 == 3)
										{
											return;
										}
										else
										{
											throw input_error();
										}
									}
								}
								catch (input_error& i)
								{
									std::cerr << i.what() << '\n';
								}
							}
						}
						if (input == 2)
						{
							return;
						}
						throw input_error();
					}
				}
				catch (input_error& i)
				{
					std::cerr << i.what() << '\n';
				}
			}
		}
		}
		if (!find)
		{
			throw search_error();
		}
	}
	catch (search_error& s)
	{
		std::cerr << s.what() << '\n';
	}
}

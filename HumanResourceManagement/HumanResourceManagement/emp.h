#pragma once
#ifndef EMP_H_
#define EMP_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class employee
{
public:
	employee();
	employee(const employee& emp);
	employee(int grade, const string& name, const string& position);
	employee(int id, int grade, const string& name, const string& position);
	virtual ~employee();

	virtual void promote() = 0;
	virtual void promote(int grade);
	virtual void pay() = 0;
	virtual void print() = 0;
	virtual void write(fstream & fs) = 0;
	void initial();

	int get_id();
	string get_position();
	string get_name();
	void set_name(string& name);
	virtual void set_sales_value(double);
	virtual void set_work_hours_per_month(int);

protected:
	static int total_emp_no_;
	int individual_emp_no_;
	int grade_;
	string name_;
	string position_;
	double monthly_salary_;
	bool valid_; //尝试通过用户使用逻辑限制前的合法性判断用数据
};

class manager : virtual public employee
{
public:
	manager();
	manager(const manager& manager);
	manager(int grade, const string& name);
	manager(int id, int grade, const string& name);
	~manager();

	virtual void promote() override;
	virtual void pay() override;
	virtual void print() override;
	void write(fstream & fs) override;

	friend ostream& operator<<(ostream& output, const manager& manager);

protected:
	static int total_manager_no_;
};

class technician : virtual public employee
{
public:
	technician();
	technician(const technician& technician);
	technician(int grade, const string& name, int work_hours_per_month);
	technician(int id, int grade, const string& name, int work_hours_per_month);
	~technician();
	virtual void promote() override;
	virtual void pay() override;
	virtual void print() override;
	virtual void write(fstream& fs) override;
	void set_work_hours_per_month(int) override;
	friend ostream& operator<<(ostream& output, const technician& technician);

protected:
	int work_hours_per_month_;
	double pay_per_hour_;
	static int total_tech_no_;
};

class salesman : virtual public employee
{
public:
	salesman();
	salesman(const salesman& salesman);
	salesman(int grade, const string& name, double sales_value);
	salesman(int id, int grade, const string& name, double sales_value);
	~salesman();
	virtual void promote() override;
	virtual void pay() override;
	virtual void print() override;
	void write(fstream& fs) override;
	void set_sales_value(double sales_value) override;
	friend ostream& operator<<(ostream& output, const salesman& salesman);
protected:
	double sales_value_;
	double commission_rate_;
};

class sales_manager final : public manager, public salesman
{
public:
	sales_manager();
	sales_manager(const sales_manager& sales_manager);
	sales_manager(int grade, const string& name, double total_sales_value);
	sales_manager(int id, int grade, const string& name, double total_sales_value);
	//sales_manager(const manager& manager);
	//sales_manager(const salesman& salesman);
	~sales_manager();
	void promote() override;
	void pay() override;
	void print() override;
	void write(fstream& fs) override;
	void set_sales_value(double) override;
	friend ostream& operator<<(ostream& output, const sales_manager& sales_manager);
	vector<int> subordinate_salesman;
protected:
	static int total_sales_manager_no_;
	double total_sales_value_;
	double commission_rate_{};
};

#endif /* EMP_H_ */

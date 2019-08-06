#include "emp.h"

int employee::total_emp_no_ = 0;

/**
 * \brief 
 */
employee::employee()
{
	individual_emp_no_ = ++total_emp_no_;
	grade_ = 0;
	name_ = "";
	position_ = "";
	monthly_salary_ = 0;
	valid_ = false;
}

/**
 * \brief 
 * \param emp 
 */
employee::employee(const employee& emp)
{
	individual_emp_no_ = emp.individual_emp_no_;
	grade_ = emp.grade_;
	name_ = emp.name_;
	position_ = emp.position_;
	monthly_salary_ = emp.monthly_salary_;
	valid_ = emp.valid_;
}

/**
 * \brief 
 * \param {int} grade 
 * \param {string} name 
 * \param {string} position 
 */
employee::employee(const int grade, const string& name, const string& position)
{
	individual_emp_no_ = ++total_emp_no_;
	grade_ = grade;
	name_ = name;
	position_ = position;
	monthly_salary_ = 0;
	valid_ = false;
}

employee::employee(const int id, const int grade, const string& name, const string& position)
{
	individual_emp_no_ = id;
	++total_emp_no_;
	total_emp_no_ = id > total_emp_no_ ? id : total_emp_no_;
	grade_ = grade;
	name_ = name;
	position_ = position;
	monthly_salary_ = 0;
	valid_ = false;
}

employee::~employee()
{
}

void employee::promote(const int grade)
{
	grade_ = grade - 1;
	promote();
}

void employee::initial()
{
	total_emp_no_ = 1;
}

int employee::get_id()
{
	return individual_emp_no_;
}

string employee::get_position()
{
	return position_;
}

string employee::get_name()
{
	return name_;
}

void employee::set_name(string& name)
{
	name_ = name;
}

void employee::set_sales_value(double)
{
}

void employee::set_work_hours_per_month(int)
{
}

int manager::total_manager_no_ = 0;

/**
 * \brief 
 */
manager::manager(): employee()
{
	position_ = "Manager";
	++total_manager_no_;
}

// * \brief 
// * \param manager 
// */
manager::manager(const manager& manager)
	: employee(manager)
{
	position_ = "Manager";
}

/**
 * \brief 
 * \param grade 
 * \param name 
 */
manager::manager(const int grade, const string& name): employee(grade, name, "Manager")
{
	++total_manager_no_;
	//monthly_salary_ = (double(grade_) - 1.0) * 2000 + 8000;
	(*this).manager::pay();
}

manager::manager(const int id, const int grade, const string& name): employee(id, grade, name, "Manager")
{
	++total_manager_no_;
	//monthly_salary_ = (double(grade_) - 1.0) * 2000 + 8000;
	(*this).manager::pay();
}

/**
 * \brief 
 */
manager::~manager()
{
	--total_manager_no_;
}

/**
 * \brief 
 */
void manager::promote()
{
	++grade_;
}

/**
 * \brief 
 */
void manager::pay()
{
	monthly_salary_ = (double(grade_) - 1.0) * 2000 + 8000;
}

/**
 * \brief 
 */
void manager::print()
{
	using namespace std;
	cout << resetiosflags(ios::right) << setiosflags(ios::left);
	cout << setw(13) << position_ << ' ';
	cout << resetiosflags(ios::left) << setiosflags(ios::right);
	cout << setw(3) << individual_emp_no_ << ' ';
	cout << resetiosflags(ios::right) << setiosflags(ios::left);
	cout << setw(20) << name_ << ' ';
	cout << resetiosflags(ios::left) << setiosflags(ios::right);
	cout << setw(2) << grade_ << ' ' << setw(6) << monthly_salary_ << '\n';
}

void manager::write(fstream& fs)
{
	fs << *this;
}


/**
 * \brief 
 * \param output 
 * \param manager 
 * \return 
 */
ostream& operator<<(ostream& output, const manager& manager)
{
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(13) << manager.position_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(3) << manager.individual_emp_no_ << ' ';
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(20) << manager.name_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(2) << manager.grade_ << ' ' << setw(6) << manager.monthly_salary_;
	return output;
}

int technician::total_tech_no_ = 0;

technician::technician(): employee()
{
	position_ = "Technician";
	work_hours_per_month_ = 0;
	pay_per_hour_ = 0;
	++total_tech_no_;
}

technician::technician(const technician& technician)
	: employee(technician)
{
	work_hours_per_month_ = technician.work_hours_per_month_;
	pay_per_hour_ = technician.pay_per_hour_;
}

technician::
technician(const int grade, const string& name, const int work_hours_per_month): employee(grade, name, "Technician"),
                                                                                 work_hours_per_month_(
	                                                                                 work_hours_per_month)
{
	++total_tech_no_;
	pay_per_hour_ = 260 * log10(10.0 * double(grade_));
	(*this).technician::pay();
}

technician::
technician(int id, const int grade, const string& name, const int work_hours_per_month) :
	employee(grade, name, "Technician"), work_hours_per_month_(work_hours_per_month)
{
	++total_tech_no_;
	pay_per_hour_ = 260 * log10(10.0 * double(grade_));
	(*this).technician::pay();
}

technician::~technician()
{
	--total_tech_no_;
}

void technician::promote()
{
	++grade_;
	pay_per_hour_ = 260 * log10(10.0 * double(grade_));
}

void technician::pay()
{
	monthly_salary_ = pay_per_hour_ * work_hours_per_month_;
}

void technician::print()
{
	cout << *this;
}

void technician::write(fstream& fs)
{
	fs << *this;
}

void technician::set_work_hours_per_month(const int work_hours_per_month)
{
	work_hours_per_month_ = work_hours_per_month;
}

ostream& operator<<(ostream& output, const technician& technician)
{
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(13) << technician.position_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(3) << technician.individual_emp_no_ << ' ';
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(20) << technician.name_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(2) << technician.grade_ << ' ' << setw(6) << technician.monthly_salary_ << ' ';
	output << setw(4) << technician.work_hours_per_month_ << ' ' << setw(6) << technician.pay_per_hour_;
	return output;
}

salesman::salesman(): employee(), sales_value_(0), commission_rate_(0)
{
}

salesman::salesman(const salesman& salesman)
	: employee(salesman)
{
	sales_value_ = salesman.sales_value_;
	commission_rate_ = salesman.commission_rate_;
}

salesman::salesman(const int grade, const string& name, const double sales_value): employee(grade, name, "Salesman"),
                                                                                   sales_value_(sales_value)
{
	commission_rate_ = 0.05 * pow(1.05, double(grade_) - 1);
	(*this).salesman::pay();
}

salesman::salesman(const int id, const int grade, const string& name, const double sales_value):
	employee(id, grade, name, "Salesman"),
	sales_value_(sales_value)
{
	commission_rate_ = 0.05 * pow(1.05, double(grade_) - 1);
	(*this).salesman::pay();
}

salesman::~salesman()
= default;

void salesman::promote()
{
	++grade_;
	commission_rate_ = 0.05 * pow(1.05, double(grade_) - 1);
}

void salesman::pay()
{
	monthly_salary_ = commission_rate_ * sales_value_;
}

void salesman::print()
{
	cout << *this;
}

void salesman::write(fstream& fs)
{
	fs << *this;
}

void salesman::set_sales_value(const double sales_value)
{
	sales_value_ = sales_value;
}

ostream& operator<<(ostream& output, const salesman& salesman)
{
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(13) << salesman.position_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(3) << salesman.individual_emp_no_ << ' ';
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(20) << salesman.name_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(2) << salesman.grade_ << ' ' << setw(6) << salesman.monthly_salary_ << ' ';
	output << setw(4) << salesman.commission_rate_ << ' ' << setw(6) << salesman.sales_value_;
	return output;
}

int sales_manager::total_sales_manager_no_ = 0;

sales_manager::sales_manager(): employee(), total_sales_value_(0), commission_rate_(0)
{
	++total_sales_manager_no_;
}

sales_manager::sales_manager(const sales_manager& sales_manager)
	: employee(sales_manager), manager(sales_manager), salesman(sales_manager)
{
	total_sales_value_ = sales_manager.total_sales_value_;
	sales_manager::commission_rate_ = sales_manager.sales_manager::commission_rate_;
}

sales_manager::
sales_manager(const int grade, const string& name, const double total_sales_value):
	employee(grade, name, "Sales_manager"), total_sales_value_(total_sales_value)
{
	++total_sales_manager_no_;
	(*this).sales_manager::pay();
}

sales_manager::
sales_manager(int id, int grade, const string& name, double total_sales_value):
	employee(id, grade, name, "Sales_manager"), total_sales_value_(total_sales_value)
{
	++total_sales_manager_no_;
	(*this).sales_manager::pay();
}

sales_manager::~sales_manager()
{
	--total_sales_manager_no_;
}

void sales_manager::promote()
{
	++grade_;
	sales_manager::commission_rate_ = 0.04 * pow(1.05, double(grade_) - 1);
}

void sales_manager::pay()
{
	monthly_salary_ = 8000 + 1000 * (double(grade_) - 1) + sales_manager::commission_rate_ * total_sales_value_;
}

void sales_manager::print()
{
	cout << *this;
}

void sales_manager::write(fstream& fs)
{
	fs << *this;
}

void sales_manager::set_sales_value(const double sales_value)
{
	total_sales_value_ = sales_value;
}

ostream& operator<<(ostream& output, const sales_manager& sales_manager)
{
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(13) << sales_manager.position_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(3) << sales_manager.individual_emp_no_ << ' ';
	output << resetiosflags(ios::right) << setiosflags(ios::left);
	output << setw(20) << sales_manager.name_ << ' ';
	output << resetiosflags(ios::left) << setiosflags(ios::right);
	output << setw(2) << sales_manager.grade_ << ' ' << setw(6) << sales_manager.monthly_salary_ << ' ';
	output << setw(4) << sales_manager.commission_rate_ << ' ' << setw(6) << sales_manager.total_sales_value_ << ' ';
	cout << '[';
	if (sales_manager.subordinate_salesman.empty())
		cout << ']';
	else
	{
		for (const auto& salesman : sales_manager.subordinate_salesman)
		{
			cout << salesman << ',';
		}
		cout << "\b]";
	}
	return output;
}

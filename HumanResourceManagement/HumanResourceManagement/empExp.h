#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <utility>

//姑且仅用于返回错误信息
//若有需求，考虑改进
class emp_exception : public std::exception
{
public:
	explicit emp_exception(std::string msg) : err_log_(std::move(msg))
	{
	}

	const char* what() const noexcept override
	{
		return err_log_.c_str();
	}

private:
	std::string err_log_;
};

class open_error : public emp_exception
{
public:
	open_error(const std::string& file_name) : emp_exception(("未打开" + file_name + "，可能文件不存在"))
	{
	}
};

class input_error : public emp_exception
{
public:
	input_error() : emp_exception("输入错误或不合规")
	{
	}
};

class search_error : public emp_exception
{
public:
	search_error(): emp_exception("未搜索到，可能不存在")
	{
	}
};

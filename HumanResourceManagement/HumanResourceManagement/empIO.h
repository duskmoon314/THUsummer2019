#pragma once
#ifndef EMPIO_H_
#define EMPIO_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "emp.h"
#include "empExp.h"



auto run(std::string file_name) -> void;

auto index(std::string& file_name) -> void;
auto explore(const std::string& file_name) -> void;
auto modify(const std::string& file_name) -> void;
auto search(const std::string& file_name) -> void;
auto change_file(std::string file_name) -> void;
auto save(std::string file_name) -> void;

auto load(const std::string& file_name, vector<employee*>& employees) -> void;

auto mod_add(vector<employee*>& employees) -> void;
auto mod_delete(vector<employee*>& employees) -> void;
auto mod_modify(vector<employee*>& employees) -> void;

#endif /* EMPIO_H_ */
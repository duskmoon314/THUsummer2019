#pragma once

#include <vector>
#include <iostream>
#include <fstream>

enum piece_color { none = 0, black = 1, white = 2 };

enum direction
{
	x_plus,
	x_minus,
	y_plus,
	y_minus,
	z_plus,
	z_minus,
	x_y_plus,
	x_y_minus,
	_x_y_plus,
	_x_y_minus,
	y_z_plus,
	y_z_minus,
	_y_z_plus,
	_y_z_minus,
	z_x_plus,
	z_x_minus,
	_z_x_plus,
	_z_x_minus,
	x_y_z_1_plus,
	x_y_z_1_minus,
	x_y_z_2_plus,
	x_y_z_2_minus,
	x_y_z_3_plus,
	x_y_z_3_minus,
	x_y_z_4_plus,
	x_y_z_4_minus
};

class point
{
public:
	point();
	point(const point& point);
	point(int z);
	point(int y, int z);
	point(int x, int y, int z);
	virtual ~point() = default;

	int get_x() const;
	int get_y() const;
	int get_z() const;

	friend std::ostream& operator<<(std::ostream& output, const point& point);
	virtual void print();
	virtual void write(std::fstream & fs);
protected:
	int x_, y_, z_;
};

//棋子
class piece : virtual public point
{
public:
	piece(int x, int y, int z);
	piece(const piece& piece);
	~piece() = default;

	void set_black();
	void set_white();
	void set_none();
	piece_color get_color() const;

	friend std::ostream& operator<<(std::ostream& output, piece& piece);
	void print() override;
	void write(std::fstream& fs) override;
protected:
	// 0 无子  1 黑  2 白
	piece_color color_ = none;
};

// 一行
class row : virtual public point
{
public:
	row(int y, int z);
	row(const row& row);
	~row() = default;

	piece& operator[](const int rank);
	friend std::ostream& operator<<(std::ostream& output, row& row);
	void print() override;
	void write(std::fstream& fs) override;
protected:
	std::vector<piece> pieces_;
};

//一层
class layer : virtual public point
{
public:
	layer(int z);
	layer(const layer& layer);
	~layer() = default;

	row& operator[](const int rank);
	piece& operator()(const int x, const int y);
	friend std::ostream& operator<<(std::ostream& output, layer& layer);
	void print() override;
	void write(std::fstream& fs) override;
protected:
	std::vector<row> rows_;
};

//棋盘
class board
{
public:
	board();
	~board() = default;

	layer& operator[](const int rank);
	row& operator()(const int y, const int z);
	piece& operator()(const int x, const int y, const int z);
	friend std::ostream& operator<<(std::ostream& output, board& board);

	piece_color check_win(const int x, const int y, const int z);
	int check_color(int x, int y, int z, direction dir, int count);
	void set_piece(int x, int y, int z, piece_color color);
protected:
	std::vector<layer> layers_;
};

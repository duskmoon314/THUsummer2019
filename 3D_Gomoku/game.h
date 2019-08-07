#pragma once

#include <vector>
#include <iostream>

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

//棋子
class piece
{
public:
	piece() = default;
	~piece() = default;

	void set_black();
	void set_white();
	piece_color get_color() const;
	friend std::ostream& operator<<(std::ostream& output, piece& piece);
protected:
	// 0 无子  1 黑  2 白
	piece_color color_ = none;
};

class row
{
public:
	row();
	~row() = default;

	piece& operator[](const int rank);
	friend std::ostream& operator<<(std::ostream& output, row& row);
protected:
	std::vector<piece> pieces_;
};

class layer
{
public:
	layer();
	~layer() = default;

	row& operator[](const int rank);
	piece& operator()(const int x, const int y);
	friend std::ostream& operator<<(std::ostream& output, layer& layer);
protected:
	std::vector<row> rows_;
};

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

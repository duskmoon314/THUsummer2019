#include "game.h"

point::point(): x_(0), y_(0), z_(0)
{
}

point::point(const point& point)
{
	x_ = point.x_;
	y_ = point.y_;
	z_ = point.z_;
}

point::point(const int z): x_(0), y_(0), z_(z)
{
}

point::point(const int y, const int z): x_(0), y_(y), z_(z)
{
}

point::point(const int x, const int y, const int z): x_(x), y_(y), z_(z)
{
}

int point::get_x() const
{
	return x_;
}

int point::get_y() const
{
	return y_;
}

int point::get_z() const
{
	return z_;
}

void point::print()
{
	std::cout << x_ << ' ' << y_ << ' ' << z_;
}

void point::write(std::fstream& fs)
{
	fs << *this;
}

piece::piece(const int x, const int y, const int z): point(x, y, z)
{
}

piece::piece(const piece& piece): point(piece)
{
	color_ = piece.color_;
}

void piece::set_black()
{
	color_ = black;
}

void piece::set_white()
{
	color_ = white;
}

void piece::set_none()
{
	color_ = none;
}

piece_color piece::get_color() const
{
	return color_;
}

void piece::print()
{
	std::cout << x_ << ' ' << y_ << ' ' << z_ << ' ' << *this;
}

void piece::write(std::fstream& fs)
{
	fs << x_ << ' ' << y_ << ' ' << z_ << ' ' << *this;
}

row::row(const int y, const int z): point(y, z)
{
	for (auto i = 0; i < 9; ++i)
	{
		pieces_.push_back(*(new piece(i, y, z)));
	}
}

row::row(const row& row)
	: point(row)
{
	pieces_ = row.pieces_;
}

piece& row::operator[](const int rank)
{
	return pieces_[rank - 1];
}

void row::print()
{
	std::cout << y_ << ' ' << z_ << ' ' << *this;
}

void row::write(std::fstream& fs)
{
	fs << y_ << ' ' << z_ << ' ' << *this;
}

layer::layer(const int z): point(z)
{
	for (auto i = 0; i < 9; ++i)
	{
		rows_.push_back(*(new row(i, z)));
	}
}

layer::layer(const layer& layer): point(layer)
{
	rows_ = layer.rows_;
}

row& layer::operator[](const int rank)
{
	return rows_[rank - 1];
}

piece& layer::operator()(const int x, const int y)
{
	return rows_[y - 1][x];
}

void layer::print()
{
	std::cout << z_ << '\n' << *this;
}

void layer::write(std::fstream& fs)
{
	fs << z_ << '\n' << *this;
}

board::board()
{
	for (auto i = 0; i < 9; ++i)
	{
		layers_.push_back(*(new layer(i)));
	}
}

layer& board::operator[](const int rank)
{
	return layers_[rank - 1];
}

row& board::operator()(const int y, const int z)
{
	return layers_[z - 1][y];
}

piece& board::operator()(const int x, const int y, const int z)
{
	return layers_[z - 1][y][x];
}

piece_color board::check_win(const int x, const int y, const int z)
{
	const auto color = (*this)(x, y, z).get_color();

	// 先沿x轴
	if (check_color(x, y, z, x_plus, 0) + check_color(x, y, z, x_minus, 0) >= 4)
	{
		return color;
	}

	// 再沿y轴
	if (check_color(x, y, z, y_plus, 0) + check_color(x, y, z, y_minus, 0) >= 4)
	{
		return color;
	}

	// 沿z轴
	if (check_color(x, y, z, z_plus, 0) + check_color(x, y, z, z_minus, 0) >= 4)
	{
		return color;
	}

	// y = x
	if (check_color(x, y, z, x_y_plus, 0) + check_color(x, y, z, x_y_minus, 0) >= 4)
	{
		return color;
	}

	// y = -x
	if (check_color(x, y, z, _x_y_plus, 0) + check_color(x, y, z, _x_y_minus, 0) >= 4)
	{
		return color;
	}

	// y = z
	if (check_color(x, y, z, y_z_plus, 0) + check_color(x, y, z, y_z_minus, 0) >= 4)
	{
		return color;
	}

	// y = -z
	if (check_color(x, y, z, _y_z_plus, 0) + check_color(x, y, z, _y_z_minus, 0) >= 4)
	{
		return color;
	}

	// x = z
	if (check_color(x, y, z, z_x_plus, 0) + check_color(x, y, z, z_x_minus, 0) >= 4)
	{
		return color;
	}

	// x = -z
	if (check_color(x, y, z, _z_x_plus, 0) + check_color(x, y, z, _z_x_minus, 0) >= 4)
	{
		return color;
	}

	// 体对角线
	if (check_color(x, y, z, x_y_z_1_plus, 0) + check_color(x, y, z, x_y_z_1_minus, 0) >= 4)
	{
		return color;
	}
	if (check_color(x, y, z, x_y_z_2_plus, 0) + check_color(x, y, z, x_y_z_2_minus, 0) >= 4)
	{
		return color;
	}
	if (check_color(x, y, z, x_y_z_3_plus, 0) + check_color(x, y, z, x_y_z_3_minus, 0) >= 4)
	{
		return color;
	}
	if (check_color(x, y, z, x_y_z_4_plus, 0) + check_color(x, y, z, x_y_z_4_minus, 0) >= 4)
	{
		return color;
	}
	return none;
}

int board::check_color(const int x, const int y, const int z, const direction dir, int count)
{
	const auto color = (*this)(x, y, z).get_color();
	switch (dir)
	{
	case x_plus:
		{
			if (x + 1 <= 9 && (*this)(x + 1, y, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y, z, dir, count);
			}
			return count;
		}
	case x_minus:
		{
			if (x - 1 > 0 && (*this)(x - 1, y, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y, z, dir, count);
			}
			return count;
		}
	case y_plus:
		{
			if (y + 1 <= 9 && (*this)(x, y + 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y + 1, z, dir, count);
			}
			return count;
		}
	case y_minus:
		{
			if (y - 1 > 0 && (*this)(x, y - 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y - 1, z, dir, count);
			}
			return count;
		}
	case z_plus:
		{
			if (z + 1 <= 9 && (*this)(x, y, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y, z + 1, dir, count);
			}
			return count;
		}
	case z_minus:
		{
			if (z - 1 > 0 && (*this)(x, y, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y, z - 1, dir, count);
			}
			return count;
		}
	case x_y_plus:
		{
			if (x + 1 <= 9 && y + 1 <= 9 && (*this)(x + 1, y + 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y + 1, z, dir, count);
			}
			return count;
		}
	case x_y_minus:
		{
			if (x - 1 > 0 && y - 1 > 0 && (*this)(x - 1, y - 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y - 1, z, dir, count);
			}
			return count;
		}
	case _x_y_plus:
		{
			if (x + 1 <= 9 && y - 1 > 0 && (*this)(x + 1, y - 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y - 1, z, dir, count);
			}
			return count;
		}
	case _x_y_minus:
		{
			if (x - 1 > 0 && y + 1 <= 9 && (*this)(x - 1, y + 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y + 1, z, dir, count);
			}
			return count;
		}
	case y_z_plus:
		{
			if (y + 1 <= 9 && z + 1 <= 9 && (*this)(x, y + 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y + 1, z + 1, dir, count);
			}
			return count;
		}
	case y_z_minus:
		{
			if (y - 1 > 0 && z - 1 > 0 && (*this)(x, y - 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y - 1, z - 1, dir, count);
			}
			return count;
		}
	case _y_z_plus:
		{
			if (y + 1 <= 9 && z - 1 > 0 && (*this)(x, y + 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y + 1, z - 1, dir, count);
			}
			return count;
		}
	case _y_z_minus:
		{
			if (y - 1 > 0 && z + 1 <= 9 && (*this)(x, y - 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y - 1, z + 1, dir, count);
			}
			return count;
		}
	case z_x_plus:
		{
			if (x + 1 <= 9 && z + 1 <= 9 && (*this)(x + 1, y, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y, z + 1, dir, count);
			}
			return count;
		}
	case z_x_minus:
		{
			if (x - 1 > 0 && z - 1 > 0 && (*this)(x - 1, y, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y, z - 1, dir, count);
			}
			return count;
		}
	case _z_x_plus:
		{
			if (x + 1 <= 9 && z - 1 > 0 && (*this)(x + 1, y, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y, z - 1, dir, count);
			}
			return count;
		}
	case _z_x_minus:
		{
			if (x - 1 > 0 && z + 1 <= 9 && (*this)(x - 1, y, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_1_plus:
		{
			if (x + 1 <= 9 && y + 1 <= 9 && z + 1 <= 9 && (*this)(x + 1, y + 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y + 1, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_1_minus:
		{
			if (x - 1 > 0 && y - 1 > 0 && z - 1 > 0 && (*this)(x - 1, y - 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y - 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_2_plus:
		{
			if (x + 1 <= 9 && y + 1 <= 9 && z - 1 > 0 && (*this)(x + 1, y + 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y + 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_2_minus:
		{
			if (x - 1 > 0 && y - 1 > 0 && z + 1 <= 9 && (*this)(x - 1, y - 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y - 1, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_3_plus:
		{
			if (x + 1 <= 9 && y - 1 > 0 && z + 1 <= 9 && (*this)(x + 1, y - 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y - 1, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_3_minus:
		{
			if (x - 1 > 0 && y + 1 <= 9 && z - 1 > 0 && (*this)(x - 1, y + 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y + 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_4_plus:
		{
			if (x + 1 <= 9 && y - 1 > 0 && z - 1 > 0 && (*this)(x + 1, y - 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y - 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_4_minus:
		{
			if (x - 1 > 0 && y + 1 <= 9 && z + 1 <= 9 && (*this)(x - 1, y + 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y + 1, z + 1, dir, count);
			}
			return count;
		}
	default:
		return count;
	}
}

void board::set_piece(const int x, const int y, const int z, const piece_color color)
{
	if (color == black)
	{
		(*this)(x, y, z).set_black();
	}
	else
	{
		(*this)(x, y, z).set_white();
	}
}

std::ostream& operator<<(std::ostream& output, const point& point)
{
	output << point.x_ << ' ' << point.y_ << ' ' << point.z_;
	return output;
}

std::ostream& operator<<(std::ostream& output, piece& piece)
{
	if (piece.color_ == none)
	{
		output << "＋";
	}
	else if (piece.color_ == black)
	{
		output << "●";
	}
	else
	{
		output << "○";
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, row& row)
{
	for (auto& piece : row.pieces_)
	{
		output << piece;
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, layer& layer)
{
	output << "  1 2 3 4 5 6 7 8 9 x\n";
	auto count = 0;
	for (auto& row : layer.rows_)
	{
		++count;
		output << count;
		output << row << '\n';
	}
	output << "y\n";
	return output;
}

std::ostream& operator<<(std::ostream& output, board& board)
{
	auto count = 0;
	for (auto& layer : board.layers_)
	{
		++count;
		output << "第" << count << "层\n\n";
		output << layer;
		output << '\n';
	}
	return output;
}

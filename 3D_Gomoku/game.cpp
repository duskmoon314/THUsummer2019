#include "game.h"

void piece::set_black()
{
	color_ = black;
}

void piece::set_white()
{
	color_ = white;
}

piece_color piece::get_color() const
{
	return color_;
}

row::row()
{
	for (auto i = 0; i < 9; ++i)
	{
		pieces_.push_back(*(new piece()));
	}
}

piece& row::operator[](const int rank)
{
	return pieces_[rank - 1];
}

layer::layer()
{
	for (auto i = 0; i < 9; ++i)
	{
		rows_.push_back(*(new row()));
	}
}

row& layer::operator[](const int rank)
{
	return rows_[rank - 1];
}

piece& layer::operator()(const int x, const int y)
{
	return rows_[y - 1][x - 1];
}

board::board()
{
	for (auto i = 0; i < 9; ++i)
	{
		layers_.push_back(*(new layer()));
	}
}

layer& board::operator[](const int rank)
{
	return layers_[rank - 1];
}

row& board::operator()(const int y, const int z)
{
	return layers_[z - 1][y - 1];
}

piece& board::operator()(const int x, const int y, const int z)
{
	return layers_[z - 1][y - 1][x - 1];
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
			if ((*this)(x + 1, y, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y, z, dir, count);
			}
			return count;
		}
	case x_minus:
		{
			if ((*this)(x - 1, y, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y, z, dir, count);
			}
			return count;
		}
	case y_plus:
		{
			if ((*this)(x, y + 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y + 1, z, dir, count);
			}
			return count;
		}
	case y_minus:
		{
			if ((*this)(x, y - 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y - 1, z, dir, count);
			}
			return count;
		}
	case z_plus:
		{
			if ((*this)(x, y, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y, z + 1, dir, count);
			}
			return count;
		}
	case z_minus:
		{
			if ((*this)(x, y, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y, z - 1, dir, count);
			}
			return count;
		}
	case x_y_plus:
		{
			if ((*this)(x + 1, y + 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y + 1, z, dir, count);
			}
			return count;
		}
	case x_y_minus:
		{
			if ((*this)(x - 1, y - 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y - 1, z, dir, count);
			}
			return count;
		}
	case _x_y_plus:
		{
			if ((*this)(x + 1, y - 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y - 1, z, dir, count);
			}
			return count;
		}
	case _x_y_minus:
		{
			if ((*this)(x - 1, y + 1, z).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y + 1, z, dir, count);
			}
			return count;
		}
	case y_z_plus:
		{
			if ((*this)(x, y + 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y + 1, z + 1, dir, count);
			}
			return count;
		}
	case y_z_minus:
		{
			if ((*this)(x, y - 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y - 1, z - 1, dir, count);
			}
			return count;
		}
	case _y_z_plus:
		{
			if ((*this)(x, y + 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y + 1, z - 1, dir, count);
			}
			return count;
		}
	case _y_z_minus:
		{
			if ((*this)(x, y - 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x, y - 1, z + 1, dir, count);
			}
			return count;
		}
	case z_x_plus:
		{
			if ((*this)(x + 1, y, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y, z + 1, dir, count);
			}
			return count;
		}
	case z_x_minus:
		{
			if ((*this)(x - 1, y, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y, z - 1, dir, count);
			}
			return count;
		}
	case _z_x_plus:
		{
			if ((*this)(x + 1, y, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y, z - 1, dir, count);
			}
			return count;
		}
	case _z_x_minus:
		{
			if ((*this)(x - 1, y, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_1_plus:
		{
			if ((*this)(x + 1, y + 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y + 1, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_1_minus:
		{
			if ((*this)(x - 1, y - 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y - 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_2_plus:
		{
			if ((*this)(x + 1, y + 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y + 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_2_minus:
		{
			if ((*this)(x - 1, y - 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y - 1, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_3_plus:
		{
			if ((*this)(x + 1, y - 1, z + 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y - 1, z + 1, dir, count);
			}
			return count;
		}
	case x_y_z_3_minus:
		{
			if ((*this)(x - 1, y + 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x - 1, y + 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_4_plus:
		{
			if ((*this)(x + 1, y - 1, z - 1).get_color() == color)
			{
				++count;
				if (count == 4) return count;
				return check_color(x + 1, y - 1, z - 1, dir, count);
			}
			return count;
		}
	case x_y_z_4_minus:
		{
			if ((*this)(x - 1, y + 1, z + 1).get_color() == color)
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

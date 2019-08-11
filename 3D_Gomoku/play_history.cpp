#include "play_history.h"

play_history_node::play_history_node(const int r, point& piece_point): point(piece_point), rank_(r),
                                                                       prev_node_(nullptr), next_node_(nullptr)
{
}

play_history_node::~play_history_node() = default;

void play_history_node::set_prev(play_history_node* prev_node)
{
	prev_node_ = prev_node;
}

void play_history_node::set_prev(play_history_node& prev_node)
{
	prev_node_ = & prev_node;
}

void play_history_node::set_next(play_history_node* next_node)
{
	next_node_ = next_node;
}

void play_history_node::set_next(play_history_node& next_point)
{
	next_node_ = & next_point;
}

play_history_node* play_history_node::get_prev() const
{
	return prev_node_;
}

play_history_node* play_history_node::get_next() const
{
	return next_node_;
}

play_history_list::play_history_list(): head_(nullptr), tail_(nullptr)
{
}

play_history_list::~play_history_list()
{
	for (auto i = 0; i < length_; ++i)
	{
		this->pop();
	}
}

void play_history_list::push(point& piece_point)
{
	auto q = new play_history_node(++length_, piece_point);
	if (head_ == nullptr)
	{
		head_ = q;
		tail_ = q;
		q->set_prev(q);
		q->set_next(nullptr);
	}
	else
	{
		tail_->set_next(q);
		q->set_prev(tail_);
		tail_ = q;
	}
}

point play_history_list::pop()
{
	if (length_ <= 0)abort();
	const auto q = tail_;
	point point(q->get_x(), q->get_y(), q->get_z());
	tail_ = tail_->get_prev();
	tail_->set_next(nullptr);
	delete q;
	--length_;
	return point;
}

void play_history_list::pop(const int times)
{
	for (auto i = 0; i < times; ++i)
	{
		this->pop();
	}
}

void play_history_list::history_pop(const int times, board& board)
{
	for (auto i = 0; i < times; ++i)
	{
		auto point = pop();
		board(point.get_x(), point.get_y(), point.get_z()).set_none();
	}
}

int play_history_list::size() const
{
	return length_;
}

void play_history_list::write(std::fstream& fs)
{
	if (head_ == nullptr)return;
	auto temp = head_;
	do
	{
		temp->write(fs);
		fs << '\n';
		temp = temp->get_next();
	} while (temp != nullptr);
	return;
}

std::ostream& operator<<(std::ostream& output, const play_history_list& list)
{
	if (list.head_ == nullptr)return output;
	auto temp = list.head_;
	do
	{
		temp->print();
		output << '\n';
		temp = temp->get_next();
	}
	while (temp != nullptr);
	return output;
}

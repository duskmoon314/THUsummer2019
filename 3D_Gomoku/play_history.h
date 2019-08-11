#pragma once
#include "game.h"

class play_history_node : virtual public point
{
public:
	play_history_node(int r, point &piece_point);
	~play_history_node();
	void set_prev(play_history_node* prev_node);
	void set_prev(play_history_node& prev_node);
	void set_next(play_history_node* next_node);
	void set_next(play_history_node& next_point);
	play_history_node* get_prev() const;
	play_history_node* get_next() const;

protected:
	int rank_;//µÚ¼¸²½
	play_history_node* prev_node_;
	play_history_node* next_node_;
};

class play_history_list
{
public:
	play_history_list();
	~play_history_list();

	void push(point &piece_point);
	point pop();
	void pop(int times);
	void history_pop(int times, board& board);
	int size() const;

	friend std::ostream& operator<<(std::ostream& output, const play_history_list& list);

private:
	int length_ = 0;
	play_history_node* head_;
	play_history_node* tail_;
};
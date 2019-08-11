#pragma once
#include "game.h"
#include "play_history.h"
#include <string>
#include <fstream>

class game_io : public board
{
public:
	game_io() = default;
	void run();
	void index();
	void play();
	void load();
	void save();
	play_history_list history;
};

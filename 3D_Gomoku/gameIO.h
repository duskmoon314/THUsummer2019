#pragma once
#include "game.h"

class game_io : public board
{
public:
	game_io() = default;
	void run();
	void index();
	void play();
};

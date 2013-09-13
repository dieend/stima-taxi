#pragma once

#include "GameState.hpp"

#include <SFML/Graphics.hpp>

class GameEngine;

class PlayState : public GameState
{
public:
	PlayState(GameEngine& game, bool replace = true);

	void pause();
	void resume();

	void update();
	void draw();
};

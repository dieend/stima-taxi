#pragma once

#include "GameState.hpp"
#include "Taxi.hpp"
#include "DrawableManager.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include "TitleState.hpp"
#include "ResourceManager.hpp"
#include "AnimatedSprite.hpp"
#include "GameEngine.hpp"
#include "Graph.hpp"
class GameEngine;

class PlayState : public GameState
{
public:
	PlayState(GameEngine& game, bool replace = true);

	void pause();
	void resume();

	void update();
	void draw();
private:
	DrawableManager dmanager;
	Taxi* taxi;
	Cities mCities;
	sf::Clock clock;
};

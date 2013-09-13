#pragma once

#include "GameState.hpp"

#include <SFML/Graphics.hpp>

class GameEngine;

class TitleState : public GameState
{
public:
	TitleState(GameEngine& game, bool replace = true);

	void pause();
	void resume();

	void update();
	void draw();

private:
	sf::Texture m_bgTex;
	sf::Texture m_textTex;
	sf::Texture m_mode1Tex;
	sf::Texture m_mode2Tex;
	sf::Texture m_mode3Tex;
	sf::Sprite m_bg;
	sf::Sprite m_text;
	sf::Sprite m_mode1;
	sf::Sprite m_mode2;
	sf::Sprite m_mode3;
};

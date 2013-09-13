#pragma once

#include <SFML/Graphics.hpp>

class Collision
{
public:
	static bool mouseOverSprite(sf::Sprite sprite, sf::RenderWindow& window);
	static bool pointOverFloatRect(float pointX, float pointY, sf::FloatRect rect);
};

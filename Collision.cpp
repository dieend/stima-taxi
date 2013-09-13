#include "Collision.hpp"

bool Collision::mouseOverSprite(sf::Sprite sprite, sf::RenderWindow& window)
{
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	return Collision::pointOverFloatRect((float)pos.x, (float)pos.y, sprite.getGlobalBounds());
}

bool Collision::pointOverFloatRect(float pointX, float pointY, sf::FloatRect rect)
{
	return (pointX >= rect.left && pointX <= rect.left + rect.width) && 
		(pointY >= rect.top && pointY <= rect.top + rect.height);
}

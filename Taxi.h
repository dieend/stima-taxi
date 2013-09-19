#pragma once
#include <SFML/Graphics.hpp>
#include "Cities.hpp"
class Taxi :
	public sf::Drawable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
	Taxi(void);
	~Taxi(void);
private:
	Cities::Route* currentRoute;
};


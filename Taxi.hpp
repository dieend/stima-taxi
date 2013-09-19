#pragma once
#include <SFML/Graphics.hpp>
#include "Cities.hpp"

class Taxi :
	public sf::Drawable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Taxi(City* location);
	~Taxi(void);
	void assignRoute(Cities::Route*);
	void update();
private:
	void updateLocation();
	City* currentLocation;
	Cities::Route* currentRoute;
	sf::RectangleShape* shape;
	double x,y;
	Cities::Route::iterator currentDestination;
};

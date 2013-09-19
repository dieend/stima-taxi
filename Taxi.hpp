#pragma once
#include <SFML/Graphics.hpp>
#include "Cities.hpp"
#include "Collision.hpp"

class Taxi :
	public sf::Drawable
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Taxi(City* location,double,double,sf::Time);
	~Taxi(void);
	void assignRoute(Cities::RouteCity*);
	void update(sf::Time);
private:
	void updateLocation();
	void updateCurrentCity();
	City* currentLocation;
	const City* startLocation;
	Cities::RouteCity* currentRoute;
	sf::RectangleShape* shape;
	double speed;
	double comfortness;
	float x,y;
	Cities::RouteCity::const_iterator* currentDestination;
	Cities::RouteCity::const_iterator* currentPreviousLocation;
	sf::Time m_frameTime;
    sf::Time m_currentTime;
    std::size_t m_currentFrame;
};

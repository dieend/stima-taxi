#include "Taxi.hpp"


Taxi::Taxi(City* location)
{
	currentLocation = location;
	shape = new sf::RectangleShape(sf::Vector2f(30,45));
	shape->setPosition(currentLocation->getX(), currentLocation->getY());
	shape->setFillColor(sf::Color::Blue);
	shape->setOutlineColor(sf::Color::Yellow);
	shape->setOutlineThickness(2.0f);
}


Taxi::~Taxi(void)
{
	delete shape;
}

void Taxi::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*shape);
}

void Taxi::assignRoute(Cities::Route*)
{
}
void Taxi::update(){
	updateLocation();
}
void Taxi::updateLocation(){}
#include "Taxi.hpp"


Taxi::Taxi(City* _startLocation, double _speed, double _comfortness, sf::Time frameTime) : startLocation(_startLocation),m_frameTime(frameTime)
{
	currentLocation = _startLocation;
	speed = _speed;
	comfortness = _comfortness;
	shape = new sf::RectangleShape(sf::Vector2f(30,45));
	x = (float)currentLocation->getX();
	y = (float)currentLocation->getY();
	shape->setFillColor(sf::Color::Blue);
	shape->setOutlineColor(sf::Color::Yellow);
	shape->setOutlineThickness(2.0f);
	currentRoute = NULL;
	currentDestination = NULL;
	currentPreviousLocation = NULL;
}


Taxi::~Taxi(void)
{
	delete shape;
}

void Taxi::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	shape->setPosition(x,y);
	target.draw(*shape);
}

void Taxi::assignRoute(Cities::RouteCity* r)
{
	currentRoute = r;
}
void Taxi::update(sf::Time deltaTime){
	updateLocation();
	updateCurrentCity();
	    // add delta time
    m_currentTime += deltaTime;

    // if current time is bigger then the frame time advance one frame
    if(m_currentTime >= m_frameTime)
    {
        // reset time, but keep the remainder
        m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());
		if (currentDestination != NULL) {
			x += dx;
			y += dy;
		}
    }
}
void Taxi::updateCurrentCity(){
	if (int(currentDestination) != NULL) {
		if (Collision::pointOverFloatRect(x,y,(**currentDestination).first->getRectangle())) {
			currentLocation = (**currentDestination).first;
			x = currentLocation->getX();
			y = currentLocation->getY();
		}
	}
}
void Taxi::updateLocation(){
	if (int(currentRoute) != NULL) {
		if (int(currentPreviousLocation) != NULL) {
			std::cout << x << " " << y << std::endl;
			if (*currentLocation == *(**currentDestination).first) {
				(*currentPreviousLocation)++;
				(*currentDestination)++;
			}
		} else {
			currentPreviousLocation = new Cities::RouteCity::const_iterator(currentRoute->begin());
			currentDestination =new Cities::RouteCity::const_iterator(currentRoute->begin());
			(*currentDestination)++;
		}
		if (*currentDestination == currentRoute->end()) {
			currentRoute = NULL;
			currentDestination = NULL;
			currentPreviousLocation = NULL;
			dx = 0;
			dy = 0;
		} else {
			double dist = (**currentDestination).second;
			double time = dist / speed;
			double totalFrame = time / m_frameTime.asSeconds();
			dx = ((**currentDestination).first->getX() - currentLocation->getX())/ totalFrame;
			dy = ((**currentDestination).first->getY() - currentLocation->getY())/ totalFrame;
		}
	}
}
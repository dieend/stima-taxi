#include "Cities.hpp"


Cities::Cities(void)
{
}


Cities::~Cities(void)
{
	for (CitiesContainerIterator it = allCities.begin(); it!=allCities.end(); ++it)
	{
		delete it->second;
	}
}

void Cities::setCityPosition(const std::string& cityName, double x, double y)
{
	City& c = *allCities[cityName];
	c.setPosition(x,y);
}
void Cities::addRoad(int i, int j,int distance)
{
	Road* r = new Road(*allCitiesIndexed[i],*allCitiesIndexed[j]);
	r->setDistance(distance);
	allRoad[i][j] = r;
	
}
void Cities::addCity(const std::string& cityName)
{
	City * c = new City(cityName);
	allCities[cityName] = c;
	allCitiesIndexed.push_back(c);
	allRoad.push_back(std::vector<Road*>());
	for (int i=0; i<allRoad.size(); i++) {
		for (int j=allRoad[i].size(); j<allRoad.size(); j++) {
			allRoad[i].push_back(NULL);
		}
	}
}


City::City(const std::string& name)
{
	mName = name;
}


City::~City(void)
{
}

void City::setPosition(double x, double y){
	px = x;
	py = y;
}

void City::draw(sf::RenderWindow& canvas){
	sf::RectangleShape node(sf::Vector2f(City::NODE_SIZE_X, City::NODE_SIZE_Y));
	node.setPosition(px - City::NODE_SIZE_X / 2, py - City::NODE_SIZE_Y / 2);
	node.setFillColor(sf::Color::White);
	canvas.draw(node);
}


Road::Road(const City& a,const City& b):A(a),B(b){}

Road::~Road(void){}

void Road::draw(sf::RenderWindow& canvas){
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(A.getX(),A.getY())),
		sf::Vertex(sf::Vector2f(B.getX(),B.getY()))
	};
	line[0].color =  sf::Color::Red;
	line[1].color =  sf::Color::Red;
	
	canvas.draw(line, 2, sf::Lines);
}
void Road::setDistance(double d){
	mDistance = d;
}

#include "Cities.hpp"


Cities::Cities(void)
{
}


Cities::~Cities(void)
{
	for (CitiesContainerIterator it = allCities.begin(); it!=allCities.end(); ++it) {
		delete it->second;
	}
}

void Cities::setCityPosition(const std::string& cityName, double x, double y)
{
	City& c = *allCities[cityName];
	c.setPosition(x,y);
}
void Cities::addRoad(int i, int j,int distance){}
void Cities::addCity(const std::string& cityName)
{
	City * c = new City(cityName);
	allCities[cityName] = c;
	allCitiesIndexed.push_back(c);
}


City::City(const std::string& name)
{
	mName = name;
}


City::~City(void)
{
}

void City::setPosition(double x, double y){}
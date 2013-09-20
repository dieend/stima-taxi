#pragma once
#include <string>
#include <iostream>
#include "Algorithm.hpp"
#include <list>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class City : public sf::Drawable
{
public:
	const static int NODE_SIZE_X = 20;
	const static int NODE_SIZE_Y = 20;
	City(const std::string& name);
	void setPosition(double x, double y);
	~City(void);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	double getX() const {return px;};
	double getY() const  {return py;};
	sf::FloatRect getRectangle();
	bool operator==(const City& c) const;
private:
	double px, py;
	std::string mName;
};

class Road : public sf::Drawable
{
public:
	Road(const City& A,const City& B);
	~Road(void);
	void setDistance(double);
	double getDistance() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	double mDistance;
	const City& A;
	const City& B;
};

class Cities : public sf::Drawable
{
public:
	typedef std::list<int> Route;
	typedef std::list<City*> RouteCity;
private:
	typedef std::map<std::string, City*> CitiesContainer;
	typedef CitiesContainer::const_iterator CitiesContainerIterator;
	typedef std::vector<std::vector<Road* > > RoadContainer;
	typedef std::vector<std::vector<RouteCity* > > RouteContainer;

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	Cities(void);
	void setCityPosition(const std::string& name, double x, double y);
	void addRoad(int i, int j, int distance);
	void addCity(const std::string&);
	City* getCity(int i);
	City* getCity(std::string);
	RouteCity* getRoute(int i, int j);
	void computeWarshal();
	~Cities(void);
private:
	CitiesContainer allCities;
	RoadContainer allRoad;
	RouteContainer allRoute;
	std::vector<City*> allCitiesIndexed;
	double** dist;
};

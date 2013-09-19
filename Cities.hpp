#pragma once
#include <string>
#include <iostream>
#include "Algorithm.hpp"
#include <list>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

class City
{
public:
	const static int NODE_SIZE_X = 20;
	const static int NODE_SIZE_Y = 20;
	City(const std::string& name);
	void setPosition(double x, double y);
	~City(void);
	void draw(sf::RenderWindow&);
	double getX() const {return px;};
	double getY() const  {return py;};
	bool operator==(const City& c) const;
private:
	double px, py;
	std::string mName;
};

class Road
{
public:
	Road(const City& A,const City& B);
	~Road(void);
	void setDistance(double);
	double getDistance() const;
	void draw(sf::RenderWindow&);
private:
	double mDistance;
	const City& A;
	const City& B;
};

class Cities
{
	typedef std::map<std::string, City*> CitiesContainer;
	typedef CitiesContainer::iterator CitiesContainerIterator;
	typedef std::vector<std::vector<Road* > > RoadContainer;
	typedef RoadContainer::iterator RoadContainerIterator;
	typedef std::list<int> Route;
	typedef std::vector<std::vector<Route* > >* RouteContainer;

public:
	Cities(void);
	void setCityPosition(const std::string& name, double x, double y);
	void addRoad(int i, int j, int distance);
	void addCity(const std::string&);
	void draw(sf::RenderWindow&);
	void computeWarshal();
	~Cities(void);
private:
	CitiesContainer allCities;
	RoadContainer allRoad;
	RouteContainer allRoute;
	std::vector<City*> allCitiesIndexed;
};

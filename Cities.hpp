#pragma once
#include <string>
#include <vector>
#include <map>
class Cities
{
	typedef std::map<std::string, City*> CitiesContainer;
	typedef CitiesContainer::iterator CitiesContainerIterator;
	typedef std::map<std::string, Road*> RoadContainer;
public:
	Cities(void);
	void setCityPosition(const std::string& name, double x, double y);
	void addRoad(int i, int j, int distance);
	void addCity(const std::string&);
	~Cities(void);
private:
	CitiesContainer allCities;
	RoadContainer allRoad;
	std::vector<const City&> allCitiesIndexed;
};

class City
{
public:
	City(const std::string& name);
	void setPosition(double x, double y);
	~City(void);
private:
	std::string mName;
};

class Road
{
public:
	Road(const City& A,const City& B);
	~Road(void);
	void setDistance(double);
private:
	double mDistance;
};

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
	for (unsigned int i=0; i<allRoad.size(); i++) {
		for (unsigned int j=0; i<allRoad[i].size(); j++) {
			delete allRoad[i][j];
		}
	}
	for (unsigned int i=0; i<allRoute->size(); i++) {
		for (unsigned int j=0; i<(*allRoute)[i].size(); j++) {
			delete (*allRoute)[i][j];
		}
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
	allRoad[j][i] = r;
}
void Cities::addCity(const std::string& cityName)
{
	City * c = new City(cityName);
	allCities[cityName] = c;
	allCitiesIndexed.push_back(c);
	allRoad.push_back(std::vector<Road*>());
	for (unsigned int i=0; i<allRoad.size(); i++) {
		for (unsigned int j=allRoad[i].size(); j<allRoad.size(); j++) {
			allRoad[i].push_back(NULL);
		}
	}
}
City* Cities::getCity(int i){
	return allCitiesIndexed[i];
}
City* Cities::getCity(std::string s){
	return allCities[s];
}
void Cities::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for (unsigned int i=0; i<allRoad.size(); i++) {
		for (unsigned int j=i+1; j<allRoad[i].size(); j++) {
			if (int(allRoad[i][j]) != 0) {
				target.draw(*allRoad[i][j]);
			}
		}
	}
	for (CitiesContainerIterator it = allCities.begin(); it!= allCities.end(); it++) {
		target.draw(*(it->second));
	}
}

void Cities::computeWarshal() {
	double ** dist = new double*[allRoad.size()];
	for (unsigned int i=0; i<allRoad.size(); i++) {
		dist[i] = new double[allRoad.size()];
	}
	for (unsigned int i=0; i<allRoad.size(); i++) {
		for (unsigned int j=0; j<allRoad[i].size(); j++) {
			if (i==j) {
				dist[i][j] = 0;
			} else if (int(allRoad[i][j]) != 0) {
				dist[i][j] = allRoad[i][j]->getDistance();
			} else {
				dist[i][j] = INF;
			}
		}
	}
	allRoute = Algorithm::computeFloydWarshall(dist,allRoad.size());
	for (unsigned int i=0; i<allRoute->size(); i++) {
		for (unsigned int j=0; j<(*allRoute)[i].size(); j++) {
			std::cout << i << " to " << j << std::endl;
			for (Route::iterator it = (*allRoute)[i][j]->begin(); it != (*allRoute)[i][j]->end(); it++) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
	}
	for (unsigned int i=0; i<allRoad.size(); i++) {
		delete[] dist[i];
	}
	delete [] dist;
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

void City::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RectangleShape node(sf::Vector2f(City::NODE_SIZE_X, City::NODE_SIZE_Y));
	node.setPosition(px - City::NODE_SIZE_X / 2, py - City::NODE_SIZE_Y / 2);
	node.setFillColor(sf::Color::White);
	target.draw(node);
}

bool City::operator==(const City& c) const{
	return mName == c.mName;
}

Road::Road(const City& a,const City& b):A(a),B(b){
	if (A.operator==(B)) {
		mDistance = 0;
	} else {
		mDistance = -1;
	}
}

Road::~Road(void){}
double Road::getDistance() const {
	return mDistance;
}
void Road::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(A.getX(),A.getY())),
		sf::Vertex(sf::Vector2f(B.getX(),B.getY()))
	};
	line[0].color =  sf::Color::Red;
	line[1].color =  sf::Color::Red;
	target.draw(line, 2, sf::Lines, states);
}
void Road::setDistance(double d){
	mDistance = d;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include "DrawableManager.hpp"

void init() {
	sf::CircleShape* shape = new sf::CircleShape(100.f);
    shape->setFillColor(sf::Color::Green);
	DrawableManager::get()["lingkarhijau"] = shape;
}


void handlePlayerInput(sf::RenderWindow& window){
	sf::Event event;
	while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}


void updateEverything(){}


void drawEverythingVisible(sf::RenderWindow& window){
	window.clear();
	for (DrawableManager::Iterator it = DrawableManager::get().begin(); it!=DrawableManager::get().end(); ++it) {
		window.draw(*it->second);
	}
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    
	init();
    while (window.isOpen())
    {
		handlePlayerInput(window);
		updateEverything();
		drawEverythingVisible(window);
    }

    return 0;
}

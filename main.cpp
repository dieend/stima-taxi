#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include "DrawableManager.hpp"

void init() {
	sf::CircleShape* shape = new sf::CircleShape(100.f);
    shape->setFillColor(sf::Color::Green);
	DrawableManager::instance().put("lingkarhijau", shape, 0);
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
	DrawableManager::instance().draw(window);
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

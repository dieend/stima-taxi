#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "DrawableManager.hpp"
#include "ResourceManager.hpp"
#include "AnimatedSprite.hpp"
void init() {
	sf::CircleShape* shape = new sf::CircleShape(50.f);
    shape->setFillColor(sf::Color::Green);
	sf::CircleShape* shape2 = new sf::CircleShape(50.f);
    shape2->setFillColor(sf::Color::Red);
	DrawableManager::instance().put("lingkar", shape, 1);

	sf::Texture* texture = new sf::Texture();
    if(!texture->loadFromFile("Resource/Gnome.png"))
		exit(EXIT_FAILURE);
	ResourceManager::instance().putTexture("gnome", texture);

	// push frames
	Animation* walkingAnimation = new Animation();
    walkingAnimation->setSpriteSheet(*texture);
    walkingAnimation->addFrame(sf::IntRect(0, 0, 53, 95));
    walkingAnimation->addFrame(sf::IntRect(53, 0, 57, 97));
    walkingAnimation->addFrame(sf::IntRect(0, 0, 53, 95));
    walkingAnimation->addFrame(sf::IntRect(110, 0, 57, 97));

    // set up AnimatesSprite
    AnimatedSprite* animatedSprite = new AnimatedSprite(sf::seconds(0.2));
    animatedSprite->setAnimation(*walkingAnimation);
//    animatedSprite.setColor(sf::Color::Red);
    animatedSprite->setPosition(100, 100);
	DrawableManager::instance().put("sprite",animatedSprite,1);
}


void handlePlayerInput(sf::RenderWindow& window){
	AnimatedSprite& animatedSprite =  dynamic_cast<AnimatedSprite&> (DrawableManager::instance().get("sprite"));
	sf::Event event;
	while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
		{
			if(animatedSprite.isPlaying())
                    animatedSprite.pause();
                else
                    animatedSprite.play();
        }    
	}
}


void updateEverything(sf::Clock& frameClock){
	AnimatedSprite& animatedSprite =  dynamic_cast<AnimatedSprite&> (DrawableManager::instance().get("sprite"));
	animatedSprite.update(frameClock.restart());
}


void drawEverythingVisible(sf::RenderWindow& window){
	window.clear();
	DrawableManager::instance().draw(window);
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    
	init();
	sf::Clock frameClock;
    while (window.isOpen())
    {
		handlePlayerInput(window);
		updateEverything(frameClock);
		drawEverythingVisible(window);
    }

    return 0;
}

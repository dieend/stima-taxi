#include "PlayState.hpp"
PlayState::PlayState( GameEngine& game, bool replace ) : GameState( game, replace )
{
	std::cout << "PlayState Init" << std::endl;
	sf::CircleShape* shape = new sf::CircleShape(50.f);
    shape->setFillColor(sf::Color::Green);
	sf::CircleShape* shape2 = new sf::CircleShape(50.f);
    shape2->setFillColor(sf::Color::Red);
	dmanager.put("lingkar", shape, 1);

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
	dmanager.put("sprite",animatedSprite,1);
}

void PlayState::pause()
{
	std::cout << "PlayState Pause" << std::endl;
}

void PlayState::resume()
{
	std::cout << "PlayState Resume" << std::endl;
}

void PlayState::update()
{
	sf::Event event;
	AnimatedSprite& animatedSprite =  dynamic_cast<AnimatedSprite&> (dmanager.get("sprite"));
	animatedSprite.update(clock.restart());
	while( m_game.getScreen().pollEvent( event ) )
	{
		switch( event.type )
		{
			case sf::Event::Closed:
				m_game.quit();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) 
				{
					m_game.lastState();
				}
				break;

		}
	}
}

void PlayState::draw()
{
	m_game.getScreen().clear();
	dmanager.draw(m_game.getScreen());
	m_game.getScreen().display();
}

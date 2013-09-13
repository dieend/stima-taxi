#include <memory>
#include <iostream>

#include "GameEngine.hpp"
#include "PlayState.hpp"

PlayState::PlayState( GameEngine& game, bool replace ) : GameState( game, replace )
{
	std::cout << "PlayState Init" << std::endl;
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

	while( m_game.getScreen().pollEvent( event ) )
	{
		switch( event.type )
		{
			case sf::Event::Closed:
				m_game.quit();
				break;
		}
	}
}

void PlayState::draw()
{
	m_game.getScreen().clear();
	m_game.getScreen().display();
}

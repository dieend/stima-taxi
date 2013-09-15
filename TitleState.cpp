#include <memory>
#include <iostream>

#include "GameEngine.hpp"
#include "TitleState.hpp"
#include "PlayState.hpp"
#include "Collision.hpp"

TitleState::TitleState(GameEngine& game, bool replace) : GameState(game, replace)
{
	m_bgTex.loadFromFile("Resource/img/title/bg.png");
	m_textTex.loadFromFile("Resource/img/title/text.png");
	m_mode1Tex.loadFromFile("Resource/img/title/mode1.png");
	m_mode2Tex.loadFromFile("Resource/img/title/mode2.png");
	m_mode3Tex.loadFromFile("Resource/img/title/mode3.png");

	m_bg.setTexture(m_bgTex, true);
	m_text.setTexture(m_textTex, true);
	m_mode1.setTexture(m_mode1Tex, true);
	m_mode2.setTexture(m_mode2Tex, true);
	m_mode3.setTexture(m_mode3Tex, true);

	m_bg.setPosition(0.f, 0.f);
	m_text.setPosition(20.f, 20.f);
	m_mode1.setPosition(20.f, 80.f);
	m_mode2.setPosition(20.f, 140.f);
	m_mode3.setPosition(20.f, 200.f);

	std::cout << "TitleState Init" << std::endl;
}

void TitleState::pause()
{
	std::cout << "TitleState Pause" << std::endl;
}

void TitleState::resume()
{
	std::cout << "TitleState Resume" << std::endl;
}

void TitleState::update()
{
	sf::Event event;

	while (m_game.getScreen().pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_game.quit();
				break;

			case sf::Event::MouseButtonPressed:
				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left:
						if (Collision::mouseOverSprite(m_mode1, m_game.getScreen()))
						{
							m_next = m_game.build<PlayState>(false);
						}

						if (Collision::mouseOverSprite(m_mode2, m_game.getScreen()))
						{
							m_next = m_game.build<PlayState>(false);
						}

						if (Collision::mouseOverSprite(m_mode3, m_game.getScreen()))
						{
							m_next = m_game.build<PlayState>(false);
						}

						break;
				}
		}
	}
}

void TitleState::draw()
{
	m_game.getScreen().clear();
	m_game.getScreen().draw(m_bg);
	m_game.getScreen().draw(m_text);
	m_game.getScreen().draw(m_mode1);
	m_game.getScreen().draw(m_mode2);
	m_game.getScreen().draw(m_mode3);
	m_game.getScreen().display();
}

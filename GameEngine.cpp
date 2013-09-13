// Copyright (c) 2012 Lukas Dürrenberger
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//    1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
//    2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
//    3. This notice may not be removed or altered from any source
//    distribution.

#include <memory>
#include <iostream>

#include "GameEngine.hpp"
#include "GameState.hpp"

GameEngine::GameEngine(const std::string& title, const unsigned int width, const unsigned int height, 
	const unsigned int bpp, const bool fullscreen) :
    m_resume(false),
	m_running(false),
	m_fullscreen(fullscreen)
{
	int flags = 0;

	if(fullscreen)
		flags = sf::Style::Fullscreen;
	else
		flags = sf::Style::Default;

	// Create render window
	screen.create(sf::VideoMode(width, height, bpp), title, flags);
	screen.setFramerateLimit(30);

	std::cout << "GameEngine Init" << std::endl;
}

void GameEngine::run(std::unique_ptr<GameState> state)
{
	m_running = true;

	m_states.push(std::move(state));
}

void GameEngine::nextState()
{
    if(m_resume)
    {
        // cleanup the current state
        if (!m_states.empty())
        {
            m_states.pop();
        }

        // resume previous state
        if (!m_states.empty())
        {
            m_states.top()->resume();
        }

        m_resume = false;
    }

	// there needs to be a state
	if (!m_states.empty())
	{
		std::unique_ptr<GameState> temp = m_states.top()->next();

		// only change states if there's a next one existing
		if(temp != nullptr)
		{
			// replace the running state
			if(temp->isReplacing())
			{
				m_states.pop();
			}
			else // pause the running state
			{
				m_states.top()->pause();
			}

			m_states.push(std::move(temp));
		}
	}
}

void GameEngine::lastState()
{
    m_resume = true;
}

void GameEngine::update()
{
	// let the state update the game
	m_states.top()->update();
}

void GameEngine::draw()
{
	// let the state draw the screen
	m_states.top()->draw();
}

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

#pragma once

#include <stack>
#include <string>
#include <memory>
#include "defines.hpp"
#include <SFML/Graphics.hpp>


class GameState;

class GameEngine
{
public:
	GameEngine(const std::string& title, const unsigned int width = WINDOW_WIDTH, 
		const unsigned int height = WINDOW_HEIGHT, const unsigned int bpp = 32, const bool fullscreen = false);

	void run(std::unique_ptr<GameState> state);

	void nextState();
	void lastState();

	void update();
	void draw();

	bool running()
	{
		return m_running;
	}

	void quit()
	{
		m_running = false;
	}

	template <typename T>
	std::unique_ptr<T> build(bool replace = true);

	sf::RenderWindow& getScreen()
	{
		return screen;
	}

private:
	sf::RenderWindow screen;

	// the stack of states
	std::stack<std::unique_ptr<GameState> > m_states;
	bool m_resume;

	bool m_running;
	bool m_fullscreen;
};

template <typename T>
std::unique_ptr<T> GameEngine::build(bool replace)
{
	return std::move(std::unique_ptr<T>(new T(*this, replace)));
}

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

#include <memory>

class GameEngine;

class GameState
{
public:
	GameState(GameEngine& game, bool replace = true) : m_game(game), m_replacing(replace) {}
	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void update() = 0;
	virtual void draw() = 0;

	std::unique_ptr<GameState> next()
	{
		return std::move(m_next);
	}

	bool isReplacing()
	{
		return m_replacing;
	}

protected:
	GameEngine& m_game;
	bool m_replacing;
	std::unique_ptr<GameState> m_next;
};

#include "DrawableManager.hpp"

//DrawableManager::Container instance;

DrawableManager::Container& DrawableManager::get()
{
	static DrawableManager::Container instance;
	return instance;
}
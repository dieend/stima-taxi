#include "DrawableContainer.hpp"

//DrawableContainer::Container instance;

DrawableContainer::Container& DrawableContainer::get()
{
	static DrawableContainer::Container instance;
	return instance;
}
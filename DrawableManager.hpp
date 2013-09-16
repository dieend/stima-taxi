#pragma once
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


class DrawableManager {
public:
	typedef std::map<std::string,sf::Drawable*> DrawableContainer;
	typedef std::vector<DrawableContainer> DrawableLayer; // drew from priority 1 (the most back location)
	typedef DrawableContainer::iterator DrawableContainerIterator;

	template <typename T>
	T& get(const std::string&);
	
	// priority: 1-5, drawed from 1 to 5. priority 0 is not drawed. 
	void put(const std::string& key, sf::Drawable* value, int priority);
	void draw(sf::RenderWindow&);
	static DrawableManager& instance();
	const static int HIDDEN_LAYER = 0;
	const static int TOP_LAYER = 4;
	DrawableManager();
	~DrawableManager();
private:
	const static int LAYER_NUMBER = 5;
	DrawableContainer allDrawables;
	DrawableLayer layers;
};
template <typename T>
T& DrawableManager::get(const std::string& key)
{
	return dynamic_cast<T&> (*allDrawables[key]);
}

#endif

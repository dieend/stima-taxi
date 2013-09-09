#ifndef __DRAWABLE_MANAGER__
#define __DRAWABLE_MANAGER__
#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


// should have priority drawing here
class DrawableManager {
public:
	typedef std::map<std::string,sf::Drawable*> DrawableContainer;
	typedef std::vector<DrawableContainer> DrawableLayer; // drew from zero priority (the most back location)
	typedef DrawableContainer::iterator DrawableContainerIterator;

	sf::Drawable& get(const std::string&);
	// priority: 1-5, drawed from 1 to 5. priority 0 is not drawed. 
	void put(const std::string& key, sf::Drawable* value, int priority);
	void draw(sf::RenderWindow&);
	static DrawableManager& instance();
	const static int HIDDEN_LAYER = 0;
	~DrawableManager();
private:
	static DrawableManager* INSTANCE;
	const static int LAYER_NUMBER = 5;
	DrawableManager();
	DrawableContainer allDrawables;
	DrawableLayer layers;
};
#endif

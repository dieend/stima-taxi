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
	void put(const std::string&, sf::Drawable*, int);
	void draw(sf::RenderWindow&);
	static DrawableManager& instance();
private:
	static DrawableManager* INSTANCE;
	DrawableManager();
	DrawableContainer allDrawables;
	DrawableLayer layers;
};

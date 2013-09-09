#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


// should have priority drawing here
class DrawableManager {
public:
	typedef std::map<std::string,sf::Drawable*> Container;
	typedef std::map<std::string,sf::Drawable*>::iterator Iterator;
	static DrawableManager::Container& get();
private:
};

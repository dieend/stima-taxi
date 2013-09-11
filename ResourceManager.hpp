#ifndef __RESOURCE_MANAGER__STIMA
#define __RESOURCE_MANAGER__STIMA
#include <map>
#include <string>
#include <SFML/Graphics.hpp>


// should have priority drawing here
class ResourceManager {
public:
	typedef std::map<std::string,sf::Texture*> ResourceContainer;
	typedef ResourceContainer::iterator ResourceContainerIterator;

	sf::Texture& getTexture(const std::string&);
	// priority: 1-5, drawed from 1 to 5. priority 0 is not drawed. 
	void putTexture(const std::string& key, sf::Texture* value);
	static ResourceManager& instance();
	const static int HIDDEN_LAYER = 0;
	~ResourceManager();
private:
	static ResourceManager* INSTANCE;
	const static int LAYER_NUMBER = 5;
	ResourceManager();
	ResourceContainer allResources;
};
#endif

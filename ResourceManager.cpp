#include "ResourceManager.hpp"

sf::Texture& ResourceManager::getTexture(const std::string& key){
	return *allResources[key];
}
void ResourceManager::putTexture(const std::string& key, sf::Texture* value){
	sf::Texture*& ref = allResources[key];
	if (ref != value) {
		sf::Texture* tmp = ref;
		ref = value;
		delete tmp;
	}
}
ResourceManager& ResourceManager::instance(){
	if (INSTANCE == NULL) {
		INSTANCE = new ResourceManager();
	}
	return *INSTANCE;
}
ResourceManager* ResourceManager::INSTANCE = NULL;
ResourceManager::ResourceManager(){}
ResourceManager::~ResourceManager(){
	for (ResourceContainerIterator it = allResources.begin(); it!=allResources.end(); ++it) {
		delete it->second;
	}
}




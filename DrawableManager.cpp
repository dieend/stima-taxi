#include "DrawableManager.hpp"

DrawableManager::DrawableManager() {
	layers = DrawableLayer(LAYER_NUMBER+1);
}
sf::Drawable& DrawableManager::get(const std::string& key){
	return *allDrawables[key];
}
void DrawableManager::put(const std::string& key, sf::Drawable* value, int priority){
	sf::Drawable*& ref = allDrawables[key];
	if (ref != value) {
		sf::Drawable* tmp = ref;
		ref = value;
		layers[priority][key] = value;
		delete tmp;
	}
}
void DrawableManager::draw(sf::RenderWindow& window){
	for (int i=1; i<=LAYER_NUMBER; i++) {
		for (DrawableContainerIterator it = layers[i].begin(); it!=layers[i].end(); ++it) {
			window.draw(*(it->second));
		}
	}
}
DrawableManager::~DrawableManager(){
	for (int i=1; i<=LAYER_NUMBER; i++) {
		for (DrawableContainerIterator it = layers[i].begin(); it!=layers[i].end(); ++it) {
			delete it->second;
		}
	}
}
#include "DrawableManager.hpp"

DrawableManager* DrawableManager::INSTANCE = NULL;

DrawableManager& DrawableManager::instance() {
	if (INSTANCE == NULL) {
		INSTANCE = new DrawableManager();
	}
	return *INSTANCE;
}
DrawableManager::DrawableManager() {
	layers = DrawableLayer(LAYER_NUMBER+1);
}
sf::Drawable& DrawableManager::get(const std::string& key){
	return *allDrawables[key];
}
void DrawableManager::put(const std::string& key, sf::Drawable* value, int priority){
	allDrawables[key] = value;
	layers[priority][key] = value;
}
void DrawableManager::draw(sf::RenderWindow& window){
	for (int i=1; i<=LAYER_NUMBER; i++) {
		for (DrawableContainerIterator it = layers[i].begin(); it!=layers[i].end(); ++it) {
			window.draw(*it->second);
		}
	}
}

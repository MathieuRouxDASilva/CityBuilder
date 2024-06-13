#ifndef API_GAMEPLAY_BUILDINGS_H_
#define API_GAMEPLAY_BUILDINGS_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "graphics/resource_manager.h"


class Building : public sf::Drawable
{
private:
	sf::Sprite sprite_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Building(const ResourceManager::Resource resource, sf::Vector2f position);
};



#endif

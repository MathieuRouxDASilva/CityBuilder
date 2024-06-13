#include "gameplay/buildings.h"

#include "graphics/resource_manager.h"


void Building::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

Building::Building(const ResourceManager::Resource resource, const sf::Vector2f position)
{
	//setup sprite_
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
	sprite_.setPosition(position);
	sprite_.setScale(1.0f, 1.0f);
}
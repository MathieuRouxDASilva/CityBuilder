#include "graphics/drawing_the_entity.h"

#include <SFML/Graphics/RenderTarget.hpp>


void DrawingEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

DrawingEntity::DrawingEntity(const ResourceManager::Resource texture, const sf::Vector2f pos)
{
	sprite_.setTexture(ResourceManager::Get().Texture(texture));
	sprite_.setPosition(pos);
}
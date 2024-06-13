#include "graphics/tile.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>


void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

Tile::Tile(const ResourceManager::Resource& resource, const sf::Vector2f position, const bool is_walkable, const bool allow_buildings)
{
	//setup sprite_
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
	sprite_.setPosition(position);
	sprite_.setScale(1.0f, 1.0f);
	is_walkable_ = is_walkable;
	allow_buildings_ = allow_buildings;
}

void Tile::set_texture(const sf::Texture& texture)
{
	sprite_.setTexture(texture);
}

void Tile::set_is_walkable(const bool is_walkable)
{
	is_walkable_ = is_walkable;
}

bool Tile::is_Walkable() const
{
	return is_walkable_;
}

bool Tile::allow_buildings() const
{
	return allow_buildings_;
}

sf::Vector2f Tile::position() const
{
	return sprite_.getPosition();
}

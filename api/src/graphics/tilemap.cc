#include <iostream>
#include "graphics/Tilemap.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "graphics/resource_manager.h"

// Fix 1 : initiate static in the cc file
sf::Vector2u Tilemap::playground_size_u_;
sf::Vector2u Tilemap::playground_tile_offset_u_ = sf::Vector2u(18, 18);

Tilemap::Tilemap(const sf::Vector2u size)
{
	tiles_.reserve(size.x * size.y);
	//define size of tilemap
	playground_size_u_ = size;
}

//generate map
void Tilemap::Generate()
{
	tiles_.clear();

	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{
			std::cout << "Add a sprite in that position " << x << ":" << y << std::endl;

			const int idx = x * playground_size_u_.y + y;
			tiles_.emplace_back() = sf::Sprite();
			tiles_[idx].setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kTerrainGround));
			tiles_[idx].setPosition(x * playground_tile_offset_u_.x, y * playground_tile_offset_u_.y);

		}
	}
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& tile : tiles_)
	{
		//std::cout << "Draw a sprite in that position " << tile.getPosition().x << ":" << tile.getPosition().y << std::endl;
		target.draw(tile, states);
	}
}

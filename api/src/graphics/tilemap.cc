#include <iostream>
#include <random>
#include "graphics/Tilemap.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include "graphics/resource_manager.h"
#include "UI/hovered_tile.h"

// Fix 1 : initiate static in the cc file
sf::Vector2u Tilemap::playground_size_u_;
sf::Vector2u Tilemap::playground_tile_size_u_ = sf::Vector2u(16, 16);
std::vector<Tile> Tilemap::tiles_;
bool Tilemap::is_map_generated_;

Tilemap::Tilemap()
{
	constexpr size_t tilemap_size_x = 100;
	constexpr size_t tilemap_size_y = 50;

	tiles_.reserve(tilemap_size_x * tilemap_size_y);
	//define size of tilemap
	playground_size_u_ = sf::Vector2u(tilemap_size_x, tilemap_size_y);
	is_map_generated_ = false;
}

//generate map
void Tilemap::Generate()
{
	is_map_generated_ = true;
	tiles_.clear();

	//for each pos
	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{
			std::cout << "Add a sprite in that position " << x << ":" << y << std::endl;

			//index to find the right tile
			const int idx = x * playground_size_u_.y + y;
			//position where the tile should be
			const auto position_for_the_tile =
				sf::Vector2f(x * playground_tile_size_u_.x, y * playground_tile_size_u_.y);

			AddingTileBasedOnRandom(position_for_the_tile);
		}
	}
}

//add tile
void Tilemap::AddingTileBasedOnRandom(const sf::Vector2f pos)
{
	//random setup
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(0, 10);
	const int rnd = uniform_dist(e1);


	if (rnd < 5)//if < 5 -> ground texture added
	{
		tiles_.emplace_back(ResourceManager::Resource::kTerrainGround,
			pos, true, true);
	}
	else if (rnd == 5)//if 5 -> sunflower texture added
	{
		tiles_.emplace_back(ResourceManager::Resource::kTerrainSunflowerGround,
			pos, true, false);
	}
	else if (rnd > 5) //if > 5 -> basic green tile added
	{
		tiles_.emplace_back(ResourceManager::Resource::kTerrainSunBasicGround,
			pos, true, true);
	}
}

//check if tile allow a building
bool Tilemap::CheckIfBuildable(const sf::Vector2i mouse_pos)
{
	if (TileAt(mouse_pos).allow_buildings())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Tilemap::HandleEvent(const sf::Event& event) const
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		//calculate pos
		const auto pos = sf::Vector2i(
			event.mouseButton.x - event.mouseButton.x % playground_tile_size_u_.x,
			event.mouseButton.y - event.mouseButton.y % playground_tile_size_u_.y);
		auto float_pos = static_cast<sf::Vector2f>(pos);

		//find tile selected
		const auto tile_found = std::find_if(tiles_.begin(), tiles_.end(),
			[&float_pos](Tile& tile) {return tile.position() == float_pos; });

		if (tile_found != tiles_.end())
		{
			if (clicked_tile_call_back_)
			{
				clicked_tile_call_back_(*tile_found);
				std::cout << "doing call_back\n";
			}
		}

	}
}

//draw
void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& t : tiles_)
	{
		target.draw(t, states);
	}
}

//get tile
Tile Tilemap::TileAt(const sf::Vector2i pos)
{
	const unsigned idx = pos.x * playground_size_u_.y + pos.y;

	return tiles_[idx];
}

//get bool 
bool Tilemap::is_map_generated()
{
	return is_map_generated_;
}

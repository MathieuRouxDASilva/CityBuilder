#include <random>
#include "graphics/Tilemap.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <tracy/Tracy.hpp>

#include "graphics/resource_manager.h"
#include "UI/hovered_tile.h"
std::random_device r;
std::default_random_engine e1(r());
std::uniform_int_distribution<int> uniform_dist(0, 10);


Tilemap::Tilemap()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	constexpr size_t tilemap_size_x = 100;
	constexpr size_t tilemap_size_y = 50;
	constexpr size_t tile_size = 16;

	//define size of tilemap and stuff
	tiles_.reserve(tilemap_size_x * tilemap_size_y);
	playground_size_u_ = sf::Vector2u(tilemap_size_x, tilemap_size_y);
	playground_tile_size_u_ = sf::Vector2u(tile_size, tile_size);


	is_map_generated_ = false;
	Generate();
}

//generate map
void Tilemap::Generate()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	tiles_.clear();

	//for each pos
	for (unsigned int x = 0; x < playground_size_u_.x; x++)
	{
		for (unsigned int y = 0; y < playground_size_u_.y; y++)
		{
			//index to find the right tile
			const int idx = x * playground_size_u_.y + y;
			//position where the tile should be
			const auto position_for_the_tile =
				sf::Vector2f(x * playground_tile_size_u_.x, y * playground_tile_size_u_.y);

			AddingTileBasedOnRandom(position_for_the_tile);
		}
	}
	is_map_generated_ = true;
}

//add tile
void Tilemap::AddingTileBasedOnRandom(const sf::Vector2f pos)
{
	//random setup
	const int rnd = uniform_dist(e1);

	if (rnd < 5)//if < 5 -> ground texture added
	{
		//set the tile we want
		Tile new_tile(ResourceManager::Resource::kTerrainGround,
			pos, true, true);

		tiles_.emplace_back(new_tile);
	}
	else if (rnd == 5)//if 5 -> sunflower texture added
	{
		//set the tile
		Tile new_tile(ResourceManager::Resource::kTerrainSunflowerGround,
			pos, true, false);

		tiles_.emplace_back(new_tile);
	}
	else if (rnd > 5) //if > 5 -> basic green tile added
	{
		Tile new_tile(ResourceManager::Resource::kTerrainBasicGround,
			pos, true, true);

		tiles_.emplace_back(new_tile);
	}
}

//check if tile allow a building
bool Tilemap::CheckIfBuildable(const sf::Vector2i mouse_pos)
{
	return TileAt(mouse_pos).allow_buildings();
}

//handle all events
void Tilemap::HandleEvent(const sf::Event& event) const
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	if (event.type == sf::Event::MouseButtonReleased)
	{
		//calculate pos
		const auto pos = sf::Vector2i(
			event.mouseButton.x - event.mouseButton.x % playground_tile_size_u_.x,
			event.mouseButton.y - event.mouseButton.y % playground_tile_size_u_.y);
		auto float_pos = static_cast<sf::Vector2f>(pos);

		//find tile selected
		const auto tile_found = std::find_if(tiles_.begin(), tiles_.end(),
			[&float_pos](const Tile& tile) {return tile.position() == float_pos; });

		if (tile_found != tiles_.end())
		{
			//do some code
			clicked_tile_call_back_();
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

	if(idx < 0 || idx > playground_size_u_.x * playground_size_u_.y || tiles_[idx].position().x < 0 || tiles_[idx].position().y > playground_size_u_.x)
	{
		Tile default_tile(ResourceManager::Resource::kTerrainGround, sf::Vector2f(0.0f, 0.0f), false, false);
		return default_tile;
	}


	return tiles_[idx];

}

sf::Vector2u Tilemap::playground_tile_size_u() const
{
	return playground_tile_size_u_;
}

//get bool 
bool Tilemap::is_map_generated() const
{
	return is_map_generated_;
}

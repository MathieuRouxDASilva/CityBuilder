#include <tracy/Tracy.hpp>

#include "gameplay/building_manager.h"
#include "gameplay/pathfinder_a_star.h"
#include "gameplay/woodsman.h"
#include "graphics/Tilemap.h"

//constructor
BuildingManager::BuildingManager(Tilemap& tilemap, EconomyManager& economy) : is_active_(false),
normal_build_cost_(4000), tilemap_(tilemap), economy_manager_(economy)
{
	buildings_.clear();
	buildings_.reserve(tilemap_.playground_tile_size_u().x * tilemap_.playground_tile_size_u().y);
	is_blue_house_mode_on_ = false;
	is_wood_house_mode_on_ = false;
}

//setup new building
void BuildingManager::SetupNewBuilding(const sf::Vector2i pos, const ResourceManager::Resource resource, Building& new_building) const
{
	new_building.setTexture(resource);

	tilemap_.TileAt(pos).set_is_walkable(false);

	tilemap_.TileAt(pos).set_allow_building(false);
}

//set a building
void BuildingManager::SetBuildingTexture(const ResourceManager::Resource resource, const sf::Vector2f position, const sf::Vector2i second_position)
{
	Building new_building(position);

	SetupNewBuilding(second_position, resource, new_building);

	buildings_.emplace_back(new_building);
}

//add a building
void BuildingManager::AddBuilding(const sf::Vector2i pos)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	if (tilemap_.CheckIfBuildable(pos))
	{
		if (economy_manager_.economy() >= normal_build_cost_)
		{
			//check tile pos
			const auto positon = tilemap_.TileAt(pos).position();

			if (is_blue_house_mode_on_)
			{
				SetBuildingTexture(ResourceManager::Resource::kBlueHouse, positon, pos);
				PopAWalker(positon);
			}
			else if (is_wood_house_mode_on_)
			{
				SetBuildingTexture(ResourceManager::Resource::kWoodHouse, positon, pos);
			}

			//cost taken
			economy_manager_.ReduceEconomyBy(normal_build_cost_);

		}
	}
	else
	{
		economy_manager_.IncreaseEconomyBy(normal_build_cost_);
	}
}

//clear vector
void BuildingManager::DestroyAllBuildings()
{
	buildings_.clear();
}

//check if tile allow building
bool BuildingManager::CheckIfBuildable(const sf::Vector2i mouse_pos) const
{
	return tilemap_.CheckIfBuildable(mouse_pos);
}

//spawns a walker at house's places
void BuildingManager::PopAWalker(const sf::Vector2f pos)
{
	WoodsMan new_walker(pos, 50.0f, tilemap_);
	constexpr int offset = 16;
	const Path path = pathfinder::CalculatePath(tilemap_.GetWalkables(), new_walker.LastDestination(), sf::Vector2f(1000.0f, 1000.0f), offset);
	new_walker.set_path(path);

	walkers_.emplace_back(new_walker);
}

//draw
void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& b : buildings_)
	{
		target.draw(b, states);
	}
	for (auto& w : walkers_)
	{
		target.draw(w, states);
	}
}

//do Ticks()
void BuildingManager::DoWalkersFromHousesTick()
{
	for (auto& w : walkers_)
	{
		w.Tick();
	}
}

//SET
void BuildingManager::set_is_active()
{
	is_active_ = !is_active_;
}
void BuildingManager::set_is_blue_house_mode_on()
{
	is_blue_house_mode_on_ = !is_blue_house_mode_on_;

	//make sure only one mode is on
	if (is_wood_house_mode_on_ && is_blue_house_mode_on_)
	{
		is_wood_house_mode_on_ = false;
	}
}
void BuildingManager::set_is_wood_house_mode_on()
{
	is_wood_house_mode_on_ = !is_wood_house_mode_on_;

	//make sure only one mode is on
	if (is_blue_house_mode_on_ && is_wood_house_mode_on_)
	{
		is_blue_house_mode_on_ = false;
	}
}

//GET
bool BuildingManager::is_active() const
{
	return is_active_;
}
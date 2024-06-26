#include "gameplay/building_manager.h"

#include <tracy/Tracy.hpp>

#include "graphics/Tilemap.h"

//constructor
BuildingManager::BuildingManager(Tilemap& tilemap, EconomyManager& economy) : normal_build_cost_(4000),
is_active_(false), tilemap_(tilemap), economy_manager_(economy) {}

//setup values
void BuildingManager::init(BuildingManager& build) const
{
	build.buildings_ = buildings_;
	build.tilemap_ = tilemap_;
	build.is_active_ = is_active_;
}

//add a building
void BuildingManager::AddBuilding(const sf::Vector2i pos, ResourceManager::Resource resource)
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

			//add a building
			auto new_building = Building(resource, positon);

			//build created
			buildings_.emplace_back(new_building);

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

//draw
void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& b : buildings_)
	{
		target.draw(b, states);
	}
}

//set some active or not
void BuildingManager::SetActive()
{
	is_active_ = !is_active_;
}

//return is_active
bool BuildingManager::is_active() const
{
	return is_active_;
}

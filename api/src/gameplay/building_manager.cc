#include "gameplay/building_manager.h"
#include "graphics/Tilemap.h"
//setup static
std::vector<Building> BuildingManager::buildings_;
bool BuildingManager::is_active_;

//constructor
BuildingManager::BuildingManager()
{
	is_active_ = false;
}

//add a building
void BuildingManager::AddBuilding(const sf::Vector2i pos, ResourceManager::Resource resource)
{
	if(CheckIfBuildable(pos))
	{
		//check tile pos
		auto positon = Tilemap::TileAt(pos).position();

		//add a building
		buildings_.emplace_back(resource, positon);
	}
}

//check if tile allow building
bool BuildingManager::CheckIfBuildable(const sf::Vector2i mouse_pos)
{
	return Tilemap::CheckIfBuildable(mouse_pos);
}

//draw
void BuildingManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto& b : buildings_)
	{
		target.draw(b, states);
	}
}

//set some active or not
void BuildingManager::SetActive()
{
	is_active_ = !is_active_;
}

bool BuildingManager::is_active()
{
	return is_active_;
}

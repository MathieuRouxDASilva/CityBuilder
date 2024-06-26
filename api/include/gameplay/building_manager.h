#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_
#include "buildings.h"
#include "economy_manager.h"
#include "graphics/tile.h"
#include "graphics/tilemap.h"


class Tilemap;

class BuildingManager : public sf::Drawable
{
private:
	size_t normal_build_cost_;
	bool is_active_;
	Tilemap& tilemap_;
	EconomyManager& economy_manager_;

	//check if it's possible
	[[nodiscard]] bool CheckIfBuildable(sf::Vector2i mouse_pos) const;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	std::vector<Building> buildings_;

	//setup build manager
	void init(BuildingManager& build) const;

	//constructor
	explicit BuildingManager(Tilemap& tilemap, EconomyManager& economy);

	//put building
	void AddBuilding(sf::Vector2i pos, ResourceManager::Resource resource);
	//reset all
	void DestroyAllBuildings();

	//Set -------------------------
	void SetActive();

	//Get -------------------------
	[[nodiscard]] bool is_active() const;

};
#endif
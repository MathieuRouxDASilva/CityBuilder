#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_
#include "buildings.h"
#include "economy_manager.h"
#include "walker.h"
#include "graphics/tile.h"
#include "graphics/tilemap.h"


class Tilemap;

class BuildingManager : public sf::Drawable
{
private:
	//all bools
	bool is_active_;
	bool is_blue_house_mode_on_;
	bool is_wood_house_mode_on_;

	//other stuff so that it speaks in other classes
	size_t normal_build_cost_;
	Tilemap& tilemap_;
	EconomyManager& economy_manager_;
	

	//vectors
	std::vector<Walker> walkers_;
	std::vector<Building> buildings_;

	//check if it's possible
	[[nodiscard]] bool CheckIfBuildable(sf::Vector2i mouse_pos) const;

	//pop a guy
	void PopAWalker(sf::Vector2f pos);

	//setup building
	void SetupNewBuilding(sf::Vector2i pos, ResourceManager::Resource resource, Building& new_building) const;
	void SetBuildingTexture(ResourceManager::Resource resource, sf::Vector2f position, sf::Vector2i second_position);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:

	//do Tick() for all walkers
	void DoWalkersFromHousesTick();

	//put building
	void AddBuilding(sf::Vector2i pos);

	//constructor
	explicit BuildingManager(Tilemap& tilemap, EconomyManager& economy);

	//reset all
	void DestroyAllBuildings();

	//Set -------------------------
	void set_is_active();
	void set_is_blue_house_mode_on();
	void set_is_wood_house_mode_on();

	//Get -------------------------
	[[nodiscard]] bool is_active() const;
};
#endif
#ifndef API_GAMEPLAY_BUILDING_MANAGER_H_
#define API_GAMEPLAY_BUILDING_MANAGER_H_
#include "buildings.h"
#include "graphics/tile.h"


class BuildingManager : public sf::Drawable
{
private:
	static bool is_active_;

	//check if it's possible
	static bool CheckIfBuildable(sf::Vector2i mouse_pos);

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	static std::vector<Building> buildings_;

	BuildingManager();

	static void AddBuilding(sf::Vector2i pos, ResourceManager::Resource resource);

	static void SetActive();

	//Get -------------------------
	[[nodiscard]] static bool is_active();

};
#endif
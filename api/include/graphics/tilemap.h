#ifndef API_TILEMAP_H_
#define API_TILEMAP_H_
#include <functional>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "tile.h"

class Tilemap final : public sf::Drawable
{
private:
	//bool to know if map generated or not
	static bool is_map_generated_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	static std::vector<Tile> tiles_;
	static sf::Vector2u playground_size_u_;
	static sf::Vector2u playground_tile_size_u_;

	//constructor
	Tilemap();

	//generate map
	static void Generate();

	//adding tiles to the vector
	static void AddingTileBasedOnRandom(sf::Vector2f pos);

	//check if the tile il buildable
	static bool CheckIfBuildable(sf::Vector2i mouse_pos);

	//events
	void HandleEvent(const sf::Event& event) const;


	//call_back
	std::function<void(Tile& tile)> clicked_tile_call_back_;

	//Get ----------------------------------------
	static Tile TileAt(sf::Vector2i pos);
	static bool is_map_generated();
};


#endif

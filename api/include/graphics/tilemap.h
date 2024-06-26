#ifndef API_TILEMAP_H_
#define API_TILEMAP_H_
#include <functional>
#include <random>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>
#include "tile.h"

class Tilemap final : public sf::Drawable
{
private:
	//bool to know if map generated or not
	bool is_map_generated_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	std::vector<Tile> tiles_;
	sf::Vector2u playground_size_u_;
	sf::Vector2u playground_tile_size_u_;
public:


	//constructor
	Tilemap();

	//generate map
	void Generate();

	//adding tiles to the vector
	void AddingTileBasedOnRandom(sf::Vector2f pos);

	//check if the tile il buildable
	bool CheckIfBuildable(sf::Vector2i mouse_pos);

	//events
	void HandleEvent(const sf::Event& event) const;

	//call_back
	std::function<void()> clicked_tile_call_back_;

	//Get ----------------------------------------
	Tile TileAt(sf::Vector2i pos);
	sf::Vector2u playground_tile_size_u() const;
	bool is_map_generated() const;
};


#endif

#include "UI/hovered_tile.h"
#include <SFML/Graphics/RenderTarget.hpp>

#include "gameplay/building_manager.h"
#include "graphics/tilemap.h"

sf::RectangleShape HoveredTile::tile_shape_;

void HoveredTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tile_shape_, states);
}

HoveredTile::HoveredTile(const sf::Vector2f size)
{
	tile_shape_.setSize(size);
	tile_shape_.setFillColor(sf::Color(100, 100, 100, 180));
	tile_shape_.setOutlineColor(sf::Color::Magenta);
	tile_shape_.setOutlineThickness(-1);
	tile_shape_.setOrigin(0, 0);
}

void HoveredTile::ChangeColor(const sf::Vector2i pos)
{
	if (Tilemap::is_map_generated() && BuildingManager::is_active())
	{
		auto position = static_cast<sf::Vector2f>(pos);

		if (Tilemap::CheckIfBuildable(pos))
		{
			set_color(sf::Color::Green);
		}
		else
		{
			set_color(sf::Color::Red);
		}
	}
	else
	{
		const auto base_color = sf::Color(100, 100, 100, 180);
		set_color(base_color);
	}
}

void HoveredTile::set_position(const sf::Vector2f position)
{
	tile_shape_.setPosition(position);
}

void HoveredTile::set_color(const sf::Color color)
{
	tile_shape_.setFillColor(color);
}

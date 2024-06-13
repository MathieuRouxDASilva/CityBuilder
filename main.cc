#include <SFML/Graphics.hpp>
#include "gameplay/building_manager.h"
#include "graphics/tilemap.h"
#include "UI/hovered_tile.h"
#include "UI/uibutton.h"


int main()
{
	//window
	sf::RenderWindow window(sf::VideoMode(1500, 800), "My window");

	//tilemap data
	Tilemap tilemap;
	auto tile_size = sf::Vector2i(tilemap.playground_tile_size_u_.x, tilemap.playground_tile_size_u_.y);

	//button data
	auto button_position = sf::Vector2f(100.0f, window.getSize().y - 100.0f);
	UiButton button(button_position, "generate");
	UiButton button_2(button_position + sf::Vector2f(100.0f * 3, 0.0f), "edit");

	//Hovered tile frame setup
	HoveredTile hover(sf::Vector2f(tile_size.x, tile_size.y));
	const auto basic_hover_color = sf::Color(100, 100, 100, 180);

	//building manager
	BuildingManager build;

	sf::Vector2i mouse_pos;
	sf::Vector2i mouse_tile_coord(mouse_pos.x / tile_size.x, mouse_pos.y / tile_size.y);


#pragma region call_backs
	//give the button a call_back func so it can pop the map
	button.call_back_ = [&tilemap]
		{
			tilemap.Generate();
		};
	//call_back to activate edit
	button_2.call_back_ = [&build]
		{
			build.SetActive();
		};
	//callback to put buildings
	tilemap.clicked_tile_call_back_ = [&build, &mouse_tile_coord](Tile& tile)
		{
			if (build.is_active())
			{
				BuildingManager::AddBuilding(mouse_tile_coord, ResourceManager::Resource::kTerrainDoor);
			}
		};
#pragma endregion

	while (window.isOpen())
	{
		//calculate mouse position and convert it in tile sized thing
		mouse_pos = sf::Mouse::getPosition(window);
		mouse_tile_coord = sf::Vector2i(mouse_pos.x / tile_size.x, mouse_pos.y / tile_size.y);

		auto mouse_tile_position = sf::Vector2f(mouse_tile_coord.x * tile_size.x,
			mouse_tile_coord.y * tile_size.y);

		//set hover frame proprely
		HoveredTile::set_position(mouse_tile_position);


		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			button.HandleEvent(event);
			button_2.HandleEvent(event);
			tilemap.HandleEvent(event);
		}

		HoveredTile::ChangeColor(mouse_tile_coord);

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(tilemap);
		window.draw(hover);
		window.draw(button);
		window.draw(button_2);
		window.draw(build);

		// end the current frame
		window.display();
	}

	return 0;
}
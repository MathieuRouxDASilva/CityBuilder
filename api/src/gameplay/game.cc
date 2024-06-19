#include "gameplay/game.h"

#include "UI/cursor.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

Game::Game()
{
	//window
	window_.create(sf::VideoMode(1500, 800), "My window");
	window_.setMouseCursorVisible(false);

	//tilemap
	tile_size_ = sf::Vector2i(tilemap_.playground_tile_size_u_.x, tilemap_.playground_tile_size_u_.y);

	//buttons setup
	const auto button_position = sf::Vector2f(100.0f, window_.getSize().y - 100.0f);
	const UiButton button_that_generate(button_position, "generate");
	const UiButton button_that_build(button_position + sf::Vector2f(100.0f * 3, 0.0f), "edit");

	//buttons
	generate_button_ = button_that_generate;
	build_mode_button_ = button_that_build;

	//hover tile setup
	const HoveredTile hover(sf::Vector2f(tile_size_.x, tile_size_.y));

	//hover
	hover_ = hover;

	//cursor
	Cursor::set_default_cursor();

	//calbacks setup
	PrepareCallBacks();
}

void Game::PrepareCallBacks()
{

	//give the button a call_back func so it can pop the map
	generate_button_.call_back_ = []
		{
			Tilemap::Generate();
		};

	//call_back to activate edit
	build_mode_button_.call_back_ = []
		{
			BuildingManager::SetActive();
			Cursor::SwapTexture();
		};

	//callback to put buildings
	tilemap_.clicked_tile_call_back_ = [this](Tile& tile)
		{
			if (BuildingManager::is_active())
			{
				BuildingManager::AddBuilding(mouse_tile_coord_, ResourceManager::Resource::kTerrainDoor);
			}
		};
}

void Game::GameLoop()
{
	Tilemap::Generate();

	while (window_.isOpen())
	{
		//calculate mouse position and convert it in tile sized thing
		mouse_pos_ = sf::Mouse::getPosition(window_);
		mouse_tile_coord_ = sf::Vector2i(mouse_pos_.x / tile_size_.x, mouse_pos_.y / tile_size_.y);

		const auto mouse_tile_position = sf::Vector2f(mouse_tile_coord_.x * tile_size_.x,
			mouse_tile_coord_.y * tile_size_.y);

		//set hover frame proprely
		HoveredTile::set_position(mouse_tile_position);
		Cursor::MoveCursor(window_);


		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window_.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_.close();
			}
			generate_button_.HandleEvent(event);
			build_mode_button_.HandleEvent(event);
			tilemap_.HandleEvent(event);
		}

		HoveredTile::ChangeColor(mouse_tile_coord_);

		// clear the window with black color
		window_.clear(sf::Color::Black);

		// draw everything here...
		window_.draw(tilemap_);
		window_.draw(generate_button_);
		window_.draw(build_mode_button_);
		window_.draw(build_);
		window_.draw(hover_);
		window_.draw(cursor_);

		// end the current frame
		window_.display();

#ifdef TRACY_ENABLE
		FrameMark;
#endif
	}
}
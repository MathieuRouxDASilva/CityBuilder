#include "gameplay/game.h"

#include "gameplay/woodsman.h"
#include "UI/cursor.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

//constructor
Game::Game() : build_(tilemap_, economy_), ui_economy_(economy_)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	window_.create(sf::VideoMode(1500, 800), "My window");
	window_.setMouseCursorVisible(false);

	// tilemap
	tile_size_ = sf::Vector2i(tilemap_.playground_tile_size_u());

	// buttons setup
	const auto button_position = sf::Vector2f(100.0f, window_.getSize().y - 100.0f);
	generate_button_ = UiButton(button_position, "generate");
	build_mode_button_ = UiButton(button_position + sf::Vector2f(100.0f * 3, 0.0f), "edit");

	// hover tile setup
	hover_ = HoveredTile(sf::Vector2f(tile_size_.x, tile_size_.y));

	// build setup
	build_.init(build_);

	// cursor
	cursor_.set_default_cursor();

	//calbacks setup
	PrepareCallBacks();
}

//init callbacks
void Game::PrepareCallBacks()
{

	//give the button a call_back func so it can pop the map
	generate_button_.call_back_ = [this]
		{
			build_.DestroyAllBuildings();
			tilemap_.Generate();
		};

	//call_back to activate edit
	build_mode_button_.call_back_ = [this]
		{
			build_.SetActive();
			cursor_.SwapTexture();
		};

	//callback to put buildings
	tilemap_.clicked_tile_call_back_ = [this]
		{
			if (build_.is_active())
			{
				build_.AddBuilding(mouse_tile_coord_, ResourceManager::Resource::kBlueHouse);
			}
		};
}

//main game loop 
void Game::GameLoop()
{
	bool is_active = false;
	bool is_buildable = false;
	WoodsMan wood(ResourceManager::Resource::kWoodsMan, sf::Vector2f(500.0f, 500.0f), 10);
	wood.DefineTexture();

	constexpr float walker_speed = 0.00016f;

	Walker walker(ResourceManager::Resource::kWoodsMan, sf::Vector2f(0.0f, 0.0f), walker_speed);
	walker.set_destination(sf::Vector2f(1000.0f, 500.0f));
	walker.DefineTexture();

	while (window_.isOpen())
	{
		CalculateMousePosition();

		SetupCursorAndHoverPositionBasedOnMousePos();

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
		//setup ui
		HoverColorSetup(is_active, is_buildable);
		ui_economy_.SetupUiEconomyText();

		
		walker.Tick();

		GraphicSetup();

		window_.draw(wood);
		window_.draw(walker);


		// end the current frame
		window_.display();

#ifdef TRACY_ENABLE
		FrameMark;
#endif
	}
}

//mouse setup position
void Game::CalculateMousePosition()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	//calculate mouse position and convert it in tile sized thing
	mouse_pos_ = sf::Mouse::getPosition(window_);
	mouse_tile_coord_ = sf::Vector2i(mouse_pos_.x / tile_size_.x, mouse_pos_.y / tile_size_.y);
}

//cursor and hover position
void Game::SetupCursorAndHoverPositionBasedOnMousePos()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	const auto mouse_tile_position = sf::Vector2f(mouse_tile_coord_.x * tile_size_.x,
		mouse_tile_coord_.y * tile_size_.y);

	//set hover frame proprely
	hover_.set_position(mouse_tile_position);
	cursor_.MoveCursor(window_);
}

//all draw() and stuff
void Game::GraphicSetup()
{
	// clear the window with black color
	window_.clear(sf::Color::Black);

	// draw everything here...
	window_.draw(tilemap_);
	window_.draw(build_);
	window_.draw(generate_button_);
	window_.draw(build_mode_button_);
	window_.draw(hover_);
	window_.draw(ui_economy_);
	window_.draw(cursor_);
}

//setup color hover
void Game::HoverColorSetup(bool& is_active, bool& is_buildable)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	if (tilemap_.is_map_generated())
	{
		is_buildable = tilemap_.CheckIfBuildable(mouse_tile_coord_);
		is_active = build_.is_active();

		hover_.ChangeColor(mouse_tile_coord_, is_active, is_buildable);
	}
}


#include "gameplay/game.h"
#include "gameplay/path.h"
#include "gameplay/pathfinder_a_star.h"
#include "gameplay/woodsman.h"
#include "UI/cursor.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

//constructor
Game::Game() : tilemap_(nature_), build_(tilemap_, economy_), ui_economy_(economy_)
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

#ifdef TRACY_ENABLE
	TracyCZoneN(window_create, "window creation", true);
#endif//window
	window_.create(sf::VideoMode(1500, 800), "My window");
	window_.setMouseCursorVisible(false);

#ifdef TRACY_ENABLE
	TracyCZoneEnd(window_create);
#endif

#ifdef TRACY_ENABLE
	TracyCZoneN(tile_size, "set tile_size", true);
#endif
	// tilemap
	tile_size_ = sf::Vector2i(tilemap_.playground_tile_size_u());

#ifdef TRACY_ENABLE
	TracyCZoneEnd(tile_size);
#endif


#ifdef TRACY_ENABLE
	TracyCZoneN(buttons, "buttons creation", true);
#endif
	// buttons setup
	const auto button_position = sf::Vector2f(100.0f, window_.getSize().y - 100.0f);
	pop_other_button_button_ = UiButton(button_position + sf::Vector2f(100.0f, 0.0f), "pop button");
	//house button
	build_mode_other_house_ = UiButton(button_position + sf::Vector2f(100.0f * 3, 0.0f), "second house");
	build_mode_other_house_.setScale(0.0f, 0.0f);
	//wood button
	build_mode_wood_house_ = UiButton(button_position + sf::Vector2f(100.0f * 3, 0.0f) * 1.8f, "wood house");
	build_mode_wood_house_.setScale(0.0f, 0.0f);

#ifdef TRACY_ENABLE
	TracyCZoneEnd(buttons);
#endif

#ifdef TRACY_ENABLE
	TracyCZoneN(hover, "hover creation", true);
#endif
	// hover tile setup
	hover_ = HoveredTile(sf::Vector2f(tile_size_));
#ifdef TRACY_ENABLE
	TracyCZoneEnd(hover);
#endif

	// cursor
	cursor_.set_default_cursor();

	//bools
	is_active_ = false;
	is_buildable_ = false;

	//calbacks setup
	PrepareCallBacks();
}

//init callbacks
void Game::PrepareCallBacks()
{
	//pop other buttons
	pop_other_button_button_.call_back_ = [this]
		{
			pop_other_button_button_.PopOtherButton(build_mode_other_house_);
			pop_other_button_button_.PopOtherButton(build_mode_wood_house_);
		};

	//setup activ buttons to pop blue houses
	build_mode_other_house_.call_back_ = [this]
		{
			//if button isn't here -> do nothing
			if (build_mode_other_house_.getScale() == sf::Vector2f(0.0f, 0.0f))
			{
				return;
			}
			//if button is clicked for the first time and the other one isn't -> activate build mode
			if (!build_mode_other_house_.is_clicked_once() && !build_mode_wood_house_.is_clicked_once())
			{
				build_.set_is_active();
				build_.set_is_blue_house_mode_on();
				build_mode_other_house_.set_is_clicked_once();
				cursor_.SwapTexture();
			}
			else if (build_mode_other_house_.is_clicked_once() && !build_mode_wood_house_.is_clicked_once()) //if pressed a second time -> deactivate it
			{
				build_.set_is_active();
				build_.set_is_blue_house_mode_on();
				build_mode_other_house_.set_is_clicked_once();
				cursor_.SwapTexture();
			}
			else if (build_mode_wood_house_.is_clicked_once()) //go from one button to another easily
			{
				build_mode_wood_house_.set_is_clicked_once();
				build_mode_other_house_.set_is_clicked_once();
				build_.set_is_blue_house_mode_on();
			}

		};

	//setup wood house
	build_mode_wood_house_.call_back_ = [this]
		{
			//if button isn't here -> do nothing
			if (build_mode_wood_house_.getScale() == sf::Vector2f(0.0f, 0.0f))
			{
				return;
			}
			//if button is clicked for the first time -> activate build mode
			if (!build_mode_wood_house_.is_clicked_once() && !build_mode_other_house_.is_clicked_once())
			{
				build_.set_is_active();
				build_.set_is_wood_house_mode_on();
				build_mode_wood_house_.set_is_clicked_once();
				cursor_.SwapTexture();
			}
			else if (build_mode_wood_house_.is_clicked_once() && !build_mode_other_house_.is_clicked_once()) //if pressed a second time -> deactivate it
			{
				build_.set_is_active();
				build_.set_is_wood_house_mode_on();
				build_mode_wood_house_.set_is_clicked_once();
				cursor_.SwapTexture();
			}
			else if (build_mode_other_house_.is_clicked_once()) //go from one button to another easily
			{
				build_mode_other_house_.set_is_clicked_once();
				build_mode_wood_house_.set_is_clicked_once();
				build_.set_is_wood_house_mode_on();
			}
		};

	//callback to put buildings
	tilemap_.clicked_tile_call_back_ = [this]
		{
			if (build_.is_active())
			{
				build_.AddBuilding(mouse_tile_coord_);
			}
		};
}

//main game loop 
void Game::GameLoop() //TODO try to put stuff in class like wood and walker
{
	tilemap_.Generate();

	constexpr float walker_speed = 50.0f;
	WoodsMan wood(sf::Vector2f(500.0f, 500.0f), walker_speed, tilemap_);
	wood.DefineTexture();


	Walker walker(sf::Vector2f(400.0f, 400.0f), walker_speed);
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
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				//set destination
				const auto destination = sf::Vector2f(
					static_cast<float>(event.mouseButton.x),
					static_cast<float>(event.mouseButton.y));


				const Path path_for_woodman = pathfinder::CalculatePath(tilemap_.GetWalkables(), wood.LastDestination(), nature_.GetATreeTilePosition(), tile_size_.x);
				const Path path_for_walker = pathfinder::CalculatePath(tilemap_.GetWalkables(), walker.LastDestination(), nature_.GetATreeTilePosition(), tile_size_.x);

				//set destination to walkers
				walker.set_path(path_for_walker);
				wood.set_path(path_for_woodman);
			}
			Events(event);
		}

		//setup ui
		HoverColorSetup(is_active_, is_buildable_);
		ui_economy_.SetupUiEconomyText();

		walker.Tick();
		wood.Tick();
		build_.DoWalkersFromHousesTick();

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

//events
void Game::Events(const sf::Event& event)
{
	//personal events
	pop_other_button_button_.HandleEvent(event);
	build_mode_other_house_.HandleEvent(event);
	build_mode_wood_house_.HandleEvent(event);
	tilemap_.HandleEvent(event);
}

//TODO find a way to put walkers event in here

//all draw() and stuff
void Game::GraphicSetup()
{
	// clear the window with black color
	window_.clear(sf::Color::Black);

	// draw everything here...
	window_.draw(tilemap_);
	window_.draw(nature_);
	window_.draw(build_);
	window_.draw(pop_other_button_button_);
	window_.draw(build_mode_other_house_);
	window_.draw(build_mode_wood_house_);
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
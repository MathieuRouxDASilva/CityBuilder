#ifndef API_GAMEPLAY_GAME_H_
#define API_GAMEPLAY_GAME_H_
#include <SFML/Graphics/RenderWindow.hpp>

#include "building_manager.h"
#include "woodsman.h"
#include "graphics/Tilemap.h"
#include "UI/cursor.h"
#include "UI/hovered_tile.h"
#include "UI/uibutton.h"
#include "UI/ui_economy.h"

class Game
{
private:
	//window
	sf::RenderWindow window_;

	//tilemap data
	Tilemap tilemap_;
	sf::Vector2i tile_size_;
	
	//generate_button_ data
	UiButton generate_button_;
	UiButton build_mode_button_;

	//Hovered tile frame setup
	HoveredTile hover_;

	//building manager
	BuildingManager build_;

	//mouse position
	sf::Vector2i mouse_pos_;
	sf::Vector2i mouse_tile_coord_;

	//cursor
	Cursor cursor_;

	//UI
	UiEconomy ui_economy_;

	//economy
	EconomyManager economy_;


	void PrepareCallBacks();
	void CalculateMousePosition();
	void SetupCursorAndHoverPositionBasedOnMousePos();
	void GraphicSetup();
	void HoverColorSetup(bool& is_active, bool& is_buildable);

public:
	//constructor
	Game();

	void GameLoop();


};


#endif //API_GAMEPLAY_GAME_H_

#include "graphics/resource_manager.h"

void ResourceManager::LoadAllTextures()
{
	blank_texture_ = sf::Texture();
	// Textures -----------------
	textures_[Resource::kYellowButton].loadFromFile("resources/PNG/button_blue_corner.png");
	textures_[Resource::kTerrainGround].loadFromFile("resources/PNG/ground.png");
	textures_[Resource::kTerrainDoor].loadFromFile("resources/PNG/door.png");
	textures_[Resource::kTerrainSunflowerGround].loadFromFile("resources/PNG/sunflower_ground.png");
	textures_[Resource::kTerrainSunBasicGround].loadFromFile("resources/PNG/basic_ground.png");
}

void ResourceManager::LoadAllFonts()
{
	default_font_ = sf::Font();
	// Fonts -------------------
	fonts_[FontsEnum::kButtonFont].loadFromFile("resources/fonts/Super Festival Personal Use.ttf");
}

void ResourceManager::LoadAllCursorTextures()
{
	default_cursor_texture_ = sf::Texture();
	//Cursor textures ------------------------
	cursor_textures_[CursorTextures::kCustomCursor].loadFromFile("resources/PNG/custom_cursor.png");
	cursor_textures_[CursorTextures::kDefaultCursor].loadFromFile("resources/PNG/custom_basic_cursor.png");
}

//constructor
ResourceManager::ResourceManager()
{
	LoadAllTextures();

	LoadAllFonts();

	LoadAllCursorTextures();
}

//get texture and returns it
sf::Texture& ResourceManager::Texture(Resource resource_id)
{
	if (textures_.contains(resource_id)) {
		return textures_.at(resource_id);
	}
	else
	{
		return blank_texture_;
	}
}

//get font and return it
sf::Font& ResourceManager::Font(FontsEnum font_id)
{
	if (fonts_.contains(font_id))
	{
		return fonts_.at(font_id);
	}
	else
	{
		return default_font_;
	}
}

//get cursor texture and return it
sf::Texture& ResourceManager::CursorTexture(CursorTextures cursor_texture_id)
{
	if (cursor_textures_.contains(cursor_texture_id))
	{
		return cursor_textures_.at(cursor_texture_id);
	}
	else
	{
		return default_cursor_texture_;
	}

}

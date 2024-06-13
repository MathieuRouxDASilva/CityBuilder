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

//constructor
ResourceManager::ResourceManager()
{
	LoadAllTextures();

	LoadAllFonts();
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

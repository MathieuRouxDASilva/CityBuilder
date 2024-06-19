#ifndef API_GRAPHICS_RESOURCE_MANAGER_H_
#define API_GRAPHICS_RESOURCE_MANAGER_H_

#include <array>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceManager
{

public:
	enum class Resource
	{
		kYellowButton,
		kTerrainGround,
		kTerrainDoor,
		kTerrainSunflowerGround,
		kTerrainSunBasicGround,
		kLength
	};

	enum class CursorTextures
	{
		kCustomCursor,
		kDefaultCursor
	};


	enum class FontsEnum
	{
		kButtonFont
	};

private:
	//textures
	std::unordered_map<Resource, sf::Texture> textures_; //TODO transform in an array
	std::array<sf::Texture, (int)Resource::kLength> textures_array_;
	sf::Texture blank_texture_;

	//fonts
	std::unordered_map<FontsEnum, sf::Font> fonts_; //TODO transform in an array
	sf::Font default_font_;

	//cursor texture
	std::unordered_map<CursorTextures, sf::Texture> cursor_textures_; //TODO transform in an array
	sf::Texture default_cursor_texture_;

	//load all textures
	void LoadAllTextures();

	//load all fonts
	void LoadAllFonts();

	//load all cursors textures
	void LoadAllCursorTextures();
public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}

	//all constructor and stuff
	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	//static ResourceManager* instantce_ = nullptr;

	//Get -----------------------
	sf::Texture& Texture(Resource resource_id);
	sf::Font& Font(FontsEnum font_id);
	sf::Texture& CursorTexture(CursorTextures cursor_texture_id);
};

#endif
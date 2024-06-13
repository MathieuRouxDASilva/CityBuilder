#ifndef API_GRAPHICS_RESOURCE_MANAGER_H_
#define API_GRAPHICS_RESOURCE_MANAGER_H_

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
		kTerrainSunBasicGround
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
	std::unordered_map<Resource, sf::Texture> textures_;
	sf::Texture blank_texture_;

	//fonts
	std::unordered_map<FontsEnum, sf::Font> fonts_;
	sf::Font default_font_;

	//cursor texture
	std::unordered_map<CursorTextures, sf::Texture> cursor_textures_;
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


	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	//Get -----------------------
	sf::Texture& Texture(Resource resource_id);
	sf::Font& Font(FontsEnum font_id);
	sf::Texture& CursorTexture(CursorTextures cursor_texture_id);
};

#endif
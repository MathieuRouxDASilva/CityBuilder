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

	//load all textures
	void LoadAllTextures();

	//load all fonts
	void LoadAllFonts();

public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}


	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	//return Texture/font
	sf::Texture& Texture(Resource resource_id);
	sf::Font& Font(FontsEnum font_id);
};

#endif
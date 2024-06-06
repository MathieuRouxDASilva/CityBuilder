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
		kTerrainGround
	};

private:
	std::unordered_map<Resource, sf::Texture> textures_;
	sf::Texture blank_texture_;

	//load all
	void LoadAllTextures();

public:
	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}


	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	sf::Texture& Texture(Resource resource_id);

};

#endif
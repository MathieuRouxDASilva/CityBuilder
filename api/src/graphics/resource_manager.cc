#include "graphics/resource_manager.h"

void ResourceManager::LoadAllTextures()
{
    // Textures -----------------
    blank_texture_ = sf::Texture();
    textures_[Resource::kYellowButton].loadFromFile("resources/PNG/button_blue_corner.png");
    textures_[Resource::kTerrainGround].loadFromFile("resources/PNG/ground.png");

}

//constructor
ResourceManager::ResourceManager()
{
    LoadAllTextures();
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
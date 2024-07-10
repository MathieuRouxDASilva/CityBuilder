#include "gameplay/buildings.h"

void Building::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kBlueHouse));
}

void Building::setTexture(const ResourceManager::Resource& resource)
{
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
}

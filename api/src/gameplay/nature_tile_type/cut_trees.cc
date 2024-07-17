#include "gameplay/nature_tile_type/cut_trees.h"

void CutTree::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kCutTree));
}

void CutTree::set_texture(const ResourceManager::Resource& resource)
{
	sprite_.setTexture(ResourceManager::Get().Texture(resource));
}
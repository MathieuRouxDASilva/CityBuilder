#ifndef API_GAMEPLAY_BUILDINGS_H_
#define API_GAMEPLAY_BUILDINGS_H_
#include "graphics/drawing_the_entity.h"
#include "graphics/resource_manager.h"


class Building : public DrawingEntity
{
public:
	//constructor
	Building(const ResourceManager::Resource texture, const sf::Vector2f pos) : DrawingEntity(texture, pos){}


	//define later
	void DefineTexture() override;
};



#endif

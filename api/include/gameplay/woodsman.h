#ifndef API_GAMEPLAY_WOODSMAN_H_
#define API_GAMEPLAY_WOODSMAN_H_
#include "walker.h"
#include "graphics/drawing_the_entity.h"


class WoodsMan : public Walker
{
public:
	//constructor
	WoodsMan(const ResourceManager::Resource resource, const sf::Vector2f pos, const float speed) : Walker(resource, pos, speed){}

	void DefineTexture() override;
};


#endif //API_GAMEPLAY_WOODSMAN_H_

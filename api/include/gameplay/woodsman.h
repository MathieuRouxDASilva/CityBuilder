#ifndef API_GAMEPLAY_WOODSMAN_H_
#define API_GAMEPLAY_WOODSMAN_H_
#include "walker.h"
#include "behavior_tree/bt_tree.h"
#include "graphics/drawing_the_entity.h"
#include "graphics/tilemap.h"


class WoodsMan : public Walker
{
private:
	behavior_tree::Tree tree_;
	Tilemap& map_;



public:
	//constructor
	WoodsMan(sf::Vector2f pos, float speed, Tilemap& map);

	//init behavior tree
	void SetBehaviorTreeNode();

	//seek wood method for behavior tree
	behavior_tree::Status SeekWood();

	//Tick()
	void Tick();

	//override
	void DefineTexture() override;
};


#endif //API_GAMEPLAY_WOODSMAN_H_

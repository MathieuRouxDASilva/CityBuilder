#include "gameplay/woodsman.h"

#include "behavior_tree/bt_leaf.h"
#include "gameplay/pathfinder_a_star.h"

using namespace behavior_tree;

//constructor
WoodsMan::WoodsMan(const sf::Vector2f pos, const float speed, Tilemap& map) : Walker(pos, speed), map_(map)
{
	DefineTexture();

	SetBehaviorTreeNode();
}

//set behavior tree
void WoodsMan::SetBehaviorTreeNode()
{
	const auto go_to_the_wood = new Leaf([this]() {return SeekWood(); }); //adding a leaf that does seekwood

	tree_.AddNode(go_to_the_wood);
}

Status WoodsMan::SeekWood()
{
	const auto destination = map_.nature().GetATreeTilePosition();
	constexpr int offset = 16;

	const Path p = pathfinder::CalculatePath(map_.GetWalkables(), LastDestination(), destination, offset);
	set_path(p);

	return Status::kSuccess;
}

//woodman tick -> what happens every frame
void WoodsMan::Tick()
{
	tree_.Tick();
	//walker.Tick() to make sure that the npc still moves
	Walker::Tick();
}

//override
void WoodsMan::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kWoodsMan));
}

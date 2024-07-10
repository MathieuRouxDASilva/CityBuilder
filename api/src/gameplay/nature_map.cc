#include "gameplay/nature_map.h"

#include <random>
static int random(const std::vector<Tree>& all_trees)
{
	std::random_device r1;
	std::default_random_engine e1(r1());
	std::uniform_int_distribution uniform_dist1(0, static_cast<int>(all_trees.size()));
	return uniform_dist1(e1);
} //TODO sometimes it goes out of bounce


//setup vector 
Nature::Nature()
{
	constexpr size_t size_x = 100;
	constexpr size_t size_y = 50;

	all_trees_.reserve(size_x * size_y);
	all_trees_.clear();
}

//add a tree tile
void Nature::AddATreeAt(const sf::Vector2f position)
{
	Tree new_tree(position);
	all_trees_.emplace_back(new_tree);
}

//return a tree position
sf::Vector2f Nature::GetATreeTilePosition() const
{
	//random setup
	const int rnd = random(all_trees_);

	return all_trees_[rnd].position();
}

void Nature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& t : all_trees_)
	{
		target.draw(t, states);
	}
}
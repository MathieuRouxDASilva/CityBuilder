#include "gameplay/nature_map.h"
#include "maths/vec2f.h"


//setup vector 
Nature::Nature()
{
	constexpr size_t size_x = 100;
	constexpr size_t size_y = 50;

	all_trees_.clear();
	all_trees_.reserve(size_x * size_y);

	all_cut_trees_.clear();
	all_cut_trees_.reserve(size_x * size_y);

	all_stones_.clear();
	all_stones_.reserve(size_x * size_y);
}

//add a tree tile
void Nature::AddATreeAt(const sf::Vector2f position)
{
	Tree new_tree(position);
	all_trees_.emplace_back(new_tree);
}
void Nature::AddAStoneAt(const sf::Vector2f position)
{
	Stone new_stone(position);
	all_stones_.emplace_back(new_stone);
}
void Nature::AddACutTree(const sf::Vector2f position)
{
	CutTree new_tree(position);
	all_cut_trees_.emplace_back(new_tree);
}
void Nature::AddACutStone(const sf::Vector2f position)
{
	MinedStone new_stone(position);
	all_cut_stones_.emplace_back(new_stone);
}

//cut tree and return if tree is here or not
bool Nature::GatherTree(sf::Vector2f pos)
{
	const auto tree = std::find_if(all_trees_.begin(), all_trees_.end(), [pos](const Tree& t) { return pos == t.position(); });

	if (tree != all_trees_.end())
	{
		const sf::Vector2f position = tree->position();
		AddACutTree(position);
		all_trees_.erase(tree);
		return true;
	}
	else
	{
		return false;
	}
}

//cut a stone
bool Nature::GatherStone(sf::Vector2f pos)
{
	const auto stone = std::find_if(all_stones_.begin(), all_stones_.end(),
		[pos](const Stone& t) { return pos == t.position(); });

	if (stone != all_stones_.end())
	{
		const sf::Vector2f position = stone->position();
		AddACutStone(position);
		all_stones_.erase(stone);
		return true;
	}
	else
	{
		return false;
	}
}

//return a tree position
sf::Vector2f Nature::GetATreeTilePosition(const sf::Vector2f starting_pos)
{
	sf::Vector2f selected_tree;
	float closest_tree_distance = std::numeric_limits<float>::infinity();

	std::for_each(all_trees_.begin(), all_trees_.end(), [&selected_tree, &starting_pos, &closest_tree_distance](const Tree& t)
		{
			const auto new_pos_square_m = squaredMagnitude(starting_pos - t.position());

			if (new_pos_square_m < closest_tree_distance)
			{
				selected_tree = t.position();
				closest_tree_distance = new_pos_square_m;
			}

		});

	return selected_tree;
}

sf::Vector2f Nature::GetAStoneTilePosition(sf::Vector2f starting_pos)
{
	sf::Vector2f selected_stone;
	float closest_stone_distance = std::numeric_limits<float>::infinity();

	std::for_each(all_stones_.begin(), all_stones_.end(), [&selected_stone, &starting_pos, &closest_stone_distance](const Stone& t)
		{
			const auto new_pos_square_m = squaredMagnitude(starting_pos - t.position());

			if (new_pos_square_m < closest_stone_distance)
			{
				selected_stone = t.position();
				closest_stone_distance = new_pos_square_m;
			}

		});

	return selected_stone;
}

void Nature::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& t : all_trees_)
	{
		target.draw(t, states);
	}

	for(auto& s: all_stones_)
	{
		target.draw(s, states);
	}

	for (auto& t : all_cut_trees_)
	{
		target.draw(t, states);
	}

	for (auto& t : all_cut_stones_)
	{
		target.draw(t, states);
	}
}
#ifndef API_GAMEPLAY_NATURE_MAP_H_
#define API_GAMEPLAY_NATURE_MAP_H_
#include "nature_tile_type/Trees.h"


class Nature final: public sf::Drawable
{
private:
	std::vector<Tree> all_trees_;
	

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Nature();

	//add a tree
	void AddATreeAt(sf::Vector2f position);

	//return a tree
	sf::Vector2f GetATreeTilePosition() const;
};




#endif //API_GAMEPLAY_NATURE_MAP_H_

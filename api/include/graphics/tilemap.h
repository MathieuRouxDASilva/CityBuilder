#ifndef API_TILEMAP_H_
#define API_TILEMAP_H_
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


enum TileType
{
	kForest,
	kPlane = 10,
	kRock = 10
};




class Tilemap : public sf::Drawable
{
private:
	int max_height_ = 10;
	int max_width_ = 10;

	//array of tiles
	TileType array_ [kPlane][kRock] = {};

	//tile by itself
	sf::RectangleShape tile_;



protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(tile_, states);
	}

public :
	//constructor
	Tilemap();

	//get size of array
	int GetSize() const;

	//draw array in numbers
	void DrawAll() const;

};










#endif

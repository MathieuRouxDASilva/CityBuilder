#include "graphics/tilemap.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>


Tilemap::Tilemap()
{

	//setup tile by default
	tile_.setSize(sf::Vector2f(20.0f, 20.0f));
	tile_.setPosition(200.0f, 200.0f);
	tile_.setFillColor(sf::Color::Magenta);



	DrawAll();
}

int  Tilemap::GetSize() const 
{
	int number_of_tiles = 0;
	for (int x = 0; x < max_width_; x++)
	{
		for (int y = 0; y < max_height_; y++)
		{
			number_of_tiles++;
		}
		std::cout << "\n\n";
	}
	return number_of_tiles;
}

void Tilemap::DrawAll() const
{
	for (int x = 0; x < max_width_; x++)
	{
		for (int y = 0; y < max_height_; y++)
		{
			const auto index = array_[x][y];

			if(index == kForest)
			{
				std::cout << "0\t";
			}

		}
		std::cout << "\n\n";
	}
}

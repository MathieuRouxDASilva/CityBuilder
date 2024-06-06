#include <SFML/Graphics.hpp>
#include "graphics/tilemap.h"
#include "UI/uibutton.h"


int main()
{
	//tiles data
	int tilemap_size_x = 25;
	int tilemap_size_y = 25;
	const auto tilemap_size = sf::Vector2u(tilemap_size_x, tilemap_size_y);
	auto tilemap = Tilemap(tilemap_size);

	//window
	sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

	//button data
	int button_height = 100;
	auto button_size = sf::Vector2f(500, 100);
	auto button_position = sf::Vector2f(window.getSize().x / 2.0f, button_height);
	UiButton button(sf::Color::Magenta, button_size, button_position);


	//give the button a call_back func so it can pop the map
	button.call_back_ = [&tilemap]()
		{
			tilemap.Generate();
		};

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			button.HandleEvent(event);
		}

		// clear the window with black color
		window.clear(sf::Color::Black);

		// draw everything here...
		window.draw(tilemap);
		window.draw(button);


		// end the current frame
		window.display();
	}

	return 0;
}
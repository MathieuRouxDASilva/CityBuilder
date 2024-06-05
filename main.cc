#include <iostream>
#include <SFML/Graphics.hpp>

#include "graphics/tilemap.h"
#include "UI/uibutton.h"


void MainCallBack()
{
	std::cout << "callback\n";
}

int main()
{
	//tiles data
	Tilemap tilemap;

	sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

	//button data
	auto button_size = sf::Vector2f(500, 100);
	auto button_position = sf::Vector2f(window.getSize().x /2.0f, 100);
	UiButton button(sf::Color::Magenta, button_size, button_position);


	
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
		window.draw(button);
		window.draw(tilemap);


		// end the current frame
		window.display();
	}

	return 0;
}
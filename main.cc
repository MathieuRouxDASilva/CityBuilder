#include <SFML/Graphics.hpp>
#include "UI/uibutton.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

	//button data
	sf::Vector2f button_size = sf::Vector2f(500, 100);
	sf::Vector2f button_position = sf::Vector2f(window.getSize().x /2, 100);
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



		// end the current frame
		window.display();
	}

	return 0;
}
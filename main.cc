#include <SFML/Graphics.hpp>
#include "UI/uibutton.h"

//button
UiButton button;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

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
        window.clear(sf::Color::Blue);

        // draw everything here...
        window.draw(button);

        

        // end the current frame
        window.display();
    }

    return 0;
}
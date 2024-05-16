#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <UI/uibutton.h>

//inplemantation of the draw function 
void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(building_button_, states);
}

//handle event init
void UiButton::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			auto mouseX = static_cast<float>(event.mouseButton.x);
			auto mouseY = static_cast<float>(event.mouseButton.y);

			if (building_button_.getGlobalBounds().contains(mouseX, mouseY))
			{
				std::cout << "xddddddddddd\n" << "\n";
			}
		}
	}
}

//constructor init
UiButton::UiButton()
{
	building_button_.setSize(sf::Vector2f(100, 100));
	building_button_.setFillColor(sf::Color(127, 0, 183));
	building_button_.setOutlineColor(sf::Color::Black);
	building_button_.setOutlineThickness(10);
	building_button_.setPosition(400, 400);
}


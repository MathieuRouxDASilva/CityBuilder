#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <UI/uibutton.h>

//inplemantation of the draw function 
void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform *= getTransform();
	target.draw(building_button_, states);
	target.draw(button_text_, states);
}

/**
 * \brief setup the button and how he looks
 */
void UiButton::SetupButton(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	//button setup
	building_button_.setSize(size);
	building_button_.setFillColor(color);
	building_button_.setOutlineColor(sf::Color::White);
	building_button_.setOutlineThickness(10);
	building_button_.setOrigin(building_button_.getSize().x /2, building_button_.getSize().y /2);
	building_button_.setPosition(position);
}

/**
 * \brief setup text on the button and how it looks
 */
void UiButton::SetupText()
{
	//font
	button_font_.loadFromFile("resources/Super Festival Personal Use.ttf");

	//text
	button_text_.setFont(button_font_);
	button_text_.setString("button");
	button_text_.setCharacterSize(24);
	button_text_.setFillColor(sf::Color::Black);
	button_text_.setStyle(sf::Text::Bold);
	button_text_.setPosition(building_button_.getPosition().x - 30, building_button_.getPosition().y);
}

//handle event init
void UiButton::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			auto mouseX = static_cast<float>(event.mouseButton.x);
			auto mouseY = static_cast<float>(event.mouseButton.y);

			if (building_button_.getGlobalBounds().contains(mouseX, mouseY))
			{
				building_button_.setScale(1, 1);
				std::cout << "xddddddddddd\n" << "\n";
				building_button_.setFillColor(sf::Color::Magenta);
			}
		}
	}
	if(event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			auto mouseX = static_cast<float>(event.mouseButton.x);
			auto mouseY = static_cast<float>(event.mouseButton.y);

			if (building_button_.getGlobalBounds().contains(mouseX, mouseY))
			{
				building_button_.setScale(0.9f, 0.9f);
				building_button_.setFillColor(sf::Color::Green);
			}
		}
	}
}

//constructor init
UiButton::UiButton(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	SetupButton(color, size, position);

	SetupText();
}

bool UiButton::IsMouseOver(const sf::RenderWindow& window) {
	auto mousePos = sf::Mouse::getPosition(window);
	return building_button_.getGlobalBounds().contains(sf::Vector2<float>(mousePos));
}

sf::RectangleShape UiButton::GetButtonShape()
{
	return building_button_;
}

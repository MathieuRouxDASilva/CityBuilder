#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <UI/uibutton.h>

//inplemantation of the draw function 
void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(button_sprite_, states);
	target.draw(button_text_, states);
}

/**
 * \brief setup the button and how he looks
 */
void UiButton::SetupButton(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	//button setup
	/*building_button_.setSize(size);
	building_button_.setFillColor(color);
	building_button_.setOutlineColor(sf::Color::White);
	building_button_.setOutlineThickness(10);
	building_button_.setOrigin(size / 2.0f);
	building_button_.setPosition(position);*/


	//set sprite and texture
	button_texture_.loadFromFile("resources/PNG/button_blue_corner.png");

	button_sprite_.setTexture(button_texture_);
	button_sprite_.setOrigin(size / 4.0f);
	button_sprite_.setColor(sf::Color::White);
	button_sprite_.setPosition(position);
}

/**
 * \brief setup text on the button and how it looks
 */
void UiButton::SetupText(sf::Vector2f position)
{
	//font
	button_font_.loadFromFile("resources/fonts/Super Festival Personal Use.ttf");

	const auto text_position = sf::Vector2f(position.x - button_sprite_.getGlobalBounds().getSize().x / 2.0f,
		position.y - button_sprite_.getGlobalBounds().getSize().y / 2.0f + 10);

	//text
	button_text_.setFont(button_font_);
	button_text_.setString("button");
	button_text_.setCharacterSize(24);
	button_text_.setFillColor(sf::Color::Black);
	button_text_.setStyle(sf::Text::Bold);
	button_text_.setPosition(text_position);
}

//handle event init
void UiButton::HandleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			const auto mouse_x = static_cast<float>(event.mouseButton.x);
			const auto mouse_y = static_cast<float>(event.mouseButton.y);

			if (button_sprite_.getGlobalBounds().contains(mouse_x, mouse_y))
			{
				SetScale(1.0f, 1.0f);
				button_sprite_.setColor(sf::Color::White);

				//---------------------------------------button's code
				//call_back_();

			}
		}
	}
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			const auto mouse_x = static_cast<float>(event.mouseButton.x);
			const auto mouse_y = static_cast<float>(event.mouseButton.y);

			if (button_sprite_.getGlobalBounds().contains(mouse_x, mouse_y))
			{
				SetScale(0.9f, 0.9f);
				button_sprite_.setColor(sf::Color::Green);
			}
		}
	}
}

void UiButton::SetScale(float factor_x, float factor_y)
{
	button_sprite_.setScale(factor_x, factor_y);
}

//constructor init
UiButton::UiButton(sf::Color color, sf::Vector2f size, sf::Vector2f position)
{
	SetupButton(color, size, position);

	SetupText(position);
}

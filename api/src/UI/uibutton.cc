#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <UI/uibutton.h>
#include "graphics/resource_manager.h"

//constructor init
UiButton::UiButton(const sf::Vector2f position,const std::string& name)
{
	SetupButton(position);

	SetupText(position, name);
}

/**
 * \brief setup the button and how he looks
 */
void UiButton::SetupButton(const sf::Vector2f position)
{
	//set sprite and texture
	button_texture_ = ResourceManager::Get().Texture(ResourceManager::Resource::kYellowButton);

	//setup button 1 -> generate map
	button_sprite_.setTexture(button_texture_);
	button_sprite_.setOrigin(button_sprite_.getLocalBounds().getSize().x /2.0f, button_sprite_.getLocalBounds().getSize().y / 2.0f);
	button_sprite_.setColor(sf::Color::White);
	button_sprite_.setPosition(position);
}

/**
 * \brief setup text on the button and how it looks
 */
void UiButton::SetupText(const sf::Vector2f position,const std::string& name)
{
	//font
	button_font_ =ResourceManager::Get().Font(ResourceManager::FontsEnum::kButtonFont);

	const auto text_position = sf::Vector2f(position.x - button_sprite_.getGlobalBounds().getSize().x / 2.0f,
		position.y - button_sprite_.getGlobalBounds().getSize().y / 2.0f + 10);

	//text
	button_text_.setFont(button_font_);
	button_text_.setString(name);
	button_text_.setCharacterSize(24);
	button_text_.setFillColor(sf::Color::Black);
	button_text_.setStyle(sf::Text::Bold);
	button_text_.setPosition(text_position);
}

//inplemantation of the draw function 
void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(button_sprite_, states);
	target.draw(button_text_, states);
}

//handle event init
void UiButton::HandleEvent(const sf::Event& event)
{
	//button 1
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
				call_back_();
				std::cout << "doing callback\n";
			}
		}
	}
}

//set button scale
void UiButton::SetScale(const float factor_x, const float factor_y)
{
	button_sprite_.setScale(factor_x, factor_y);
}


#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_
#include <functional>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


//class that wil make a generate_button_ appear in sfml window
class UiButton : public sf::Drawable, public sf::Transformable
{
private:
	sf::Sprite button_sprite_;
	sf::Texture button_texture_;

	//text and font
	sf::Text button_text_;

	//setup for constructor
	void SetupButton(sf::Vector2f position);
	void SetupText(sf::Vector2f position, const std::string& name);

protected:
	//draw function
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructors
	UiButton() = default;
	UiButton(sf::Vector2f position, const std::string& name);
	UiButton(const UiButton& other) = default;
	UiButton& operator=(const UiButton& other) = default;

	//function that handle events
	void HandleEvent(const sf::Event& event);

	//Set ---------------------------
	void SetScale(float factor_x, float factor_y);

	//call back
	std::function<void()> call_back_;
};





#endif //API_UI_UIBUTTON_H_
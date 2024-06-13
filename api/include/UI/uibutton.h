#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_
#include <functional>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


//class that wil make a button appear in sfml window
class UiButton : public sf::Drawable, public sf::Transformable
{
private:
	//button related variables
	sf::RectangleShape building_button_;
	sf::Sprite button_sprite_;
	sf::Texture button_texture_;

	//text and font
	sf::Text button_text_;
	sf::Font button_font_;


	//draw function
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//setup for constructor
	void SetupButton(sf::Vector2f position);
	void SetupText(sf::Vector2f position,const std::string& name);
public :
	//constructor
	UiButton(sf::Vector2f position,const std::string& name);
	//function that handle events
	void HandleEvent(const sf::Event& event);

	//set scale
	void SetScale(float factor_x, float factor_y);

	//call back
	std::function<void()> call_back_;
};





#endif //API_UI_UIBUTTON_H_
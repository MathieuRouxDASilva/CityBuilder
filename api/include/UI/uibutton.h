#ifndef API_UI_UIBUTTON_H_
#define API_UI_UIBUTTON_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

//clas that wil make a button appear in sfml window
class UiButton : public sf::Drawable, public sf::Transformable
{
	//button shape
	sf::RectangleShape building_button_;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	

public :
	//constructor
	UiButton();
	void HandleEvent(const sf::Event& event);



};





#endif //API_UI_UIBUTTON_H_
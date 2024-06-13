#ifndef UI_HOVERED_TILE_H_
#define UI_HOVERED_TILE_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class HoveredTile: public sf::Drawable
{
private:
	static sf::RectangleShape tile_shape_;


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	explicit HoveredTile(sf::Vector2f size);

	//allow feedbacks on if tile is buildable or not
	static void ChangeColor(sf::Vector2i pos);

	//Set -------------------------------
	static void set_position(sf::Vector2f position);
	static void set_color(sf::Color color);
};




#endif

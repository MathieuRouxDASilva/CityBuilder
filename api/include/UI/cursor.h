#ifndef API_UI_CURSOR_H_
#define API_UI_CURSOR_H_
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Window.hpp>



class Cursor : public sf::Drawable
{
private:
	static sf::Sprite cursor_sprite_;
	static bool is_default_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructor
	Cursor();

	//move cursor
	static void MoveCursor(const sf::Window& window);

	//swap texture
	static void SwapTexture();

	//Set ----------------------
	static void set_custom_cursor();
	static void set_default_cursor();


};
#endif
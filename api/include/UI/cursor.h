#ifndef API_UI_CURSOR_H_
#define API_UI_CURSOR_H_
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Window.hpp>


class Cursor
{
private:
	sf::Cursor custom_cursor_;
	sf::Cursor default_cursor_;
public:
	//Set ----------------------

	void set_custom_cursor(sf::Window& window) const;
	void set_default_cursor(sf::Window& window) const;
};
#endif
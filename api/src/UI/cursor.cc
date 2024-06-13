#include "UI/cursor.h"

void Cursor::set_custom_cursor(sf::Window& window) const
{
	window.setMouseCursor(custom_cursor_);
}

void Cursor::set_default_cursor(sf::Window& window) const
{
	window.setMouseCursor(default_cursor_);
}

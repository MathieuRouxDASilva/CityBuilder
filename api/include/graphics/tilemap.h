#ifndef API_TILEMAP_H_
#define API_TILEMAP_H_
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

class Tilemap : public sf::Drawable
{

public:

	static sf::Vector2u playground_size_u_;
	static sf::Vector2u playground_tile_offset_u_;

	explicit Tilemap(const sf::Vector2u size);

	void Generate();


	Tilemap() = default;

private:
	std::vector<sf::Sprite> tiles_;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};


#endif

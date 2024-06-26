#ifndef API_UI_UI_ECONOMY_H_
#define API_UI_UI_ECONOMY_H_
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>

#include "gameplay/economy_manager.h"


class UiEconomy : public sf::Drawable
{
private:
	sf::Text economy_text_;
	EconomyManager& economy_manager_;
	size_t economy_amount_;

	

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	//constructor
	UiEconomy(EconomyManager& economy);

	//setup ui text
	void SetupUiEconomyText();
};

#endif //API_UI_UI_ECONOMY_H_
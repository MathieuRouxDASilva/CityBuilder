#include "UI/ui_economy.h"

#include <tracy/Tracy.hpp>

#include "graphics/resource_manager.h"

//change text
void UiEconomy::SetupUiEconomyText()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif
	//little calcul
	economy_amount_ = economy_manager_.economy();
	economy_text_.setString(std::to_string(economy_amount_));
}

//draw
void UiEconomy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(economy_text_, states);
}

//constructor
UiEconomy::UiEconomy(EconomyManager& economy) : economy_manager_(economy)
{
	const auto text_pos = sf::Vector2f(0.0f, 0.0f);

	//setup text
	economy_text_.setFont(ResourceManager::Get().Font(ResourceManager::FontsEnum::kArial));
	economy_text_.setCharacterSize(24);
	economy_text_.setFillColor(sf::Color::Black);
	economy_text_.setStyle(sf::Text::Bold);
	economy_text_.setPosition(text_pos);
	SetupUiEconomyText();
}
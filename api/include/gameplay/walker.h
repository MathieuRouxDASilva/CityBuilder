#ifndef API_GAMEPLAY_WALKER_H_
#define API_GAMEPLAY_WALKER_H_
#include <chrono>
#include <SFML/Graphics/Transformable.hpp>

#include "graphics/drawing_the_entity.h"

//class responsible for any entity mouvement 
class Walker : public sf::Transformable, public DrawingEntity
{
	//TODO 1. destination, 2. framerate independency, 3. close to steering behavior 
private:
	//chrono variable
	std::chrono::time_point<std::chrono::steady_clock> last_time_;
	sf::Vector2f destination_;
	float linear_speed_;

public:
	Walker(ResourceManager::Resource texture, const sf::Vector2f& pos, float speed);

	//every second thing
	void Tick();

	//define virtual
	void DefineTexture() override;


	//Set ----------------
	void set_destination(sf::Vector2f pos);
	void set_linear_speed(float speed);
};
#endif //API_GAMEPLAY_WALKER_H_
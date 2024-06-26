#include "gameplay/walker.h"

#include "../../../core/include/maths/vec2f.h"

Walker::Walker(const ResourceManager::Resource texture, const sf::Vector2f& pos, const float speed) : DrawingEntity(texture, pos)
{
	set_linear_speed(speed);
	last_time_ = std::chrono::steady_clock::now();
}

//action every tick
void Walker::Tick()
{
	//clock system
	const auto now{ std::chrono::steady_clock::now() };
	const std::chrono::duration<float> elapsed_seconds{ now - last_time_ };
	const auto delta_time = elapsed_seconds;
	const auto delta = delta_time.count();

	//calculate direction
	const sf::Vector2f actual_pos = getPosition();
	const sf::Vector2f direction = destination_ - actual_pos;
	//normalise this direction
	const auto normalized_direction = core::Vec2f(direction.x, direction.y);
	normalized_direction.Normalise();
	//divide it
	const auto divided_direction = sf::Vector2f(normalized_direction.x * linear_speed_ * delta, normalized_direction.y * linear_speed_ * delta);

	//set it
	setPosition(actual_pos + divided_direction);
	sprite_.setPosition(getPosition());
}

//define walker
void Walker::DefineTexture()
{
}

//set destination
void Walker::set_destination(const sf::Vector2f pos)
{
	destination_ = pos;
}

//set speed
void Walker::set_linear_speed(const float speed)
{
	linear_speed_ = speed;
}
#include "gameplay/walker.h"
#include <tracy/Tracy.hpp>

#include "../../core/include/maths/vec2f.h"

Walker::Walker(const sf::Vector2f& pos, const float speed) : DrawingEntity(pos)
{
	SetTextureAndDebugShape();

	set_linear_speed(speed);
	last_time_ = std::chrono::steady_clock::now();
}

//definetexture() + debug_shape in drawing_entity.h
void Walker::SetTextureAndDebugShape()
{
	DefineTexture();

	debug_shape_.setPosition(sprite_.getGlobalBounds().getPosition());
	debug_shape_.setSize(sprite_.getGlobalBounds().getSize());
}

sf::Vector2f Walker::LastDestination() const
{
	return destination_;
}

//action every tick
void Walker::Tick()
{
#ifdef TRACY_ENABLE
	ZoneScoped;
#endif

	//chrono system
	const auto now{ std::chrono::steady_clock::now() };
	const std::chrono::duration<float> elapsed_seconds{ now - last_time_ };
	last_time_ = std::chrono::steady_clock::now();

	//loop of calcul to go tile by tile
	if (path_.is_available())
	{
		// Positionning -------------------------------
		const sf::Vector2f actual_position = getPosition();
		const sf::Vector2f direction = destination_ - actual_position;
		//normalise
		const auto normalized_direction = core::Vec2f(direction.x, direction.y);
		normalized_direction.Normalise();
		//magnitude
		const auto magnitude_direction = core::Vec2f(direction.x, direction.y);


		sf::Vector2f new_position = sf::Vector2f(0, 0);
		constexpr int tile_size = 16;


		if (magnitude_direction.Magnitude() < 0.01f * tile_size)
		{
			new_position = destination_;
			destination_ = path_.GetNextStep();
		}
		else
		{
			new_position = actual_position + sf::Vector2f(
				direction.x * linear_speed_ * elapsed_seconds.count(),
				direction.y * linear_speed_ * elapsed_seconds.count()
			);
		}

		// Update positions ---------------------------
		setPosition(new_position);
		sprite_.setPosition(new_position);
		debug_shape_.setPosition(new_position);

	}
}

//define walker
void Walker::DefineTexture()
{
	sprite_.setTexture(ResourceManager::Get().Texture(ResourceManager::Resource::kWoodsMan));
}


//SET
void Walker::set_destination(const sf::Vector2f pos)
{
	destination_ = pos;
}
void Walker::set_linear_speed(const float speed)
{
	linear_speed_ = speed;
}
void Walker::set_path(const Path& path)
{
	path_ = path;
}
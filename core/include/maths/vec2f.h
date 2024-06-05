#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_
#include <cmath>
#include <complex>

#include "vec2i.h"

namespace core
{
	/**
	 * \brief Vec2f is a struct that allow basic maths
	 */
	struct Vec2f
	{
		float x = 0, y = 0;

		//Vec2f() = default;

		//// Constructor from Vec2f
		//explicit Vec2f(const Vec2i& vec) : x(static_cast<float>(vec.x)), y(static_cast<float>(vec.y)) {}

		//// Constructor
		//Vec2f(float x, float y) : x(x), y(y) {}

		//add system
		constexpr Vec2f operator+(Vec2f other)const
		{
			return { x + other.x , y + other.y };
		}

		//sub system
		constexpr Vec2f operator-(Vec2f other)const
		{
			return { x - other.x, y - other.y };
		}

		//negative numbers system
		constexpr Vec2f operator-()const
		{
			return { -x, -y };
		}

		//multiply
		constexpr Vec2f operator*(float scalaire) const
		{
			return { x * scalaire, y * scalaire };
		}

		//divide
		constexpr Vec2f operator/(float scalar) const
		{
			if (scalar == 0)
			{
				//can't devide by 0
				std::terminate();
			}
			else
			{
				return { x / scalar, y / scalar };
			}
		}

		//dot product (produit scalaire) system
		static constexpr float Dot(Vec2f v1, Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		//perpenducular
		[[nodiscard]] constexpr Vec2f Perpendicular() const //FAIRE perpendicular 2
		{
			return { -y, x };
		}

		//Lerp
		[[nodiscard]] static constexpr Vec2f Lerp(Vec2f a, Vec2f b, float t)
		{
			return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
		}

		//normalise and sqr normalise your vector
		[[nodiscard]] Vec2f  Normalise() const
		{
			const float mag = Magnitude();
			if (mag == 0)
			{
				std::terminate();
			}
			return { x / mag, y / mag };
		}


		//calculate magnitude and sqr magnitude
		[[nodiscard]] float Magnitude() const
		{
			const float length = std::sqrt(x * x + y * y);
			return  length;
		}

		[[nodiscard]] constexpr float SqrMagnitude() const
		{
			const float length = x * x + y * y;
			return  length;
		}


	}; //struct Vec2i

	//operator for float in left side
	constexpr Vec2f operator*(float t, const Vec2f& vec)
	{
		return { t * vec.x, t * vec.y };
	}
	constexpr Vec2f operator/(float t, const Vec2f& vec)
	{
		return { t /vec.x, t / vec.y };
	}

} //namespace core

#endif //CORE_MATHS_VEC2I_H_
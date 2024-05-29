#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_
#include <iostream>
#include <cmath>
#include <complex>

namespace core
{
	/**
	 * \brief Vec2f is a struct that allow basic maths
	 */
	struct Vec2f
	{
		float x = 0, y = 0;

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
		constexpr Vec2f operator/(float scalaire) const
		{
			if (scalaire == 0)
			{
				std::cerr << "deviding by 0\n";
			}
			else
			{
				return { x / scalaire, y / scalaire };
			}
		}

		//dot product (produit scalaire) system
		static constexpr int Dot(Vec2f v1, Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		//perpenducular
		constexpr Vec2f Perpendicular() const
		{
			return { -y, x };
		}

		//Lerp
		constexpr Vec2f Lerp(Vec2f a, Vec2f b, float t) const
		{
			return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
		}

		//normalise and sqr normalise your vector
		Vec2f  Normalise() const
		{
			const float mag = Magnitude();
			if (mag == 0)
			{
				throw std::invalid_argument("Cannot normalize a zero vector");
			}
			return { x / mag, y / mag };
		}
		Vec2f SqrNormalise() const
		{
			return { x / SqrMagnitude(),y / SqrMagnitude() };
		}


		//calculate magnitude and sqr magnitude
		float Magnitude() const
		{
			const float length = std::sqrt(x * x + y * y);
			return  length;
		}
		float SqrMagnitude() const
		{
			const float length = x * x + y * y;
			return  length;
		}


	}; //struct Vec2i



} //namespace core

#endif //CORE_MATHS_VEC2I_H_
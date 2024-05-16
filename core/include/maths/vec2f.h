#ifndef CORE_MATHS_VEC2F_H_
#define CORE_MATHS_VEC2F_H_

namespace core
{
	/**
	 * \brief Vec2f is a struct that allow basic maths
	 */
	struct Vec2f
	{
		float x = 0, y = 0;

		//const means that x and y will not be changed
		constexpr Vec2f operator+(Vec2f other)const
		{
			return { x + other.x , y + other.y };
		}

		constexpr Vec2f operator-(Vec2f other)const
		{
			return { x - other.x, y - other.y };
		}

		constexpr Vec2f operator-()const
		{
			return { -x, -y };
		}

		static constexpr int Dot(Vec2f v1, Vec2f v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		constexpr Vec2f Perpendicular() const
		{
			return { -y, x };
		}



	}; //struct Vec2i



} //namespace core

#endif //CORE_MATHS_VEC2I_H_
#ifndef CORE_MATHS_VEC2I_H_
#define CORE_MATHS_VEC2I_H_
#include <iostream>
#include <__msvc_sanitizer_annotate_container.hpp>

namespace core
{
	/**
	 * \brief Vec2i is a struct that allow basic maths
	 */
	struct Vec2i
{
    int x = 0, y = 0;

    //const means that x and y will not be changed
    constexpr Vec2i operator+(Vec2i other)const //constexpr -> operator+'s result is calculated in compile time -> make it easier
    {
        return {x + other.x , y + other.y};
    }

    constexpr Vec2i operator-(Vec2i other)const
	{
        return {x - other.x, y - other.y };
    }

    constexpr Vec2i operator-()const
    {
        return {-x, -y};
    }

    static constexpr int Dot(Vec2i v1, Vec2i v2)
    {
        return v1.x * v2.x + v1.y * v2.y;
    }

    constexpr Vec2i Perpendicular() const
    {
        return { -y, x };
    }
    constexpr Vec2i operator*(int scalar) const
    {
        return { x * scalar, y * scalar};
    }
    constexpr Vec2i operator/(int scalar) const
    {
        if(scalar == 0)
        {
            throw std::invalid_argument("Division by zero");
        }
        else
        {
            return { x / scalar, y / scalar };
        }
    }



}; //struct Vec2i



} //namespace core

 #endif //CORE_MATHS_VEC2I_H_
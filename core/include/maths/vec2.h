#ifndef CORE_MATHS_VEC2_H_
#define CORE_MATHS_VEC2_H_

#include <iostream>
#include <stdexcept>

namespace core
{
    template <typename T>
    struct Vec2
    {
        T x = 0, y = 0;

        // Default constructor
        Vec2() = default;

        // Constructor from another Vec2 with different type
        template <typename U>
        Vec2(const Vec2<U>& vec)
            : x(static_cast<T>(vec.x)), y(static_cast<T>(vec.y)) {}

        // Addition operator
        constexpr Vec2 operator+(Vec2 other) const
        {
            return { x + other.x, y + other.y };
        }

        // Subtraction operator
        constexpr Vec2 operator-(Vec2 other) const
        {
            return { x - other.x, y - other.y };
        }

        // Unary minus operator
        constexpr Vec2 operator-() const
        {
            return { -x, -y };
        }

        // Dot product
        static constexpr T Dot(Vec2 v1, Vec2 v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        // Perpendicular vector
        constexpr Vec2 Perpendicular() const
        {
            return { -y, x };
        }

        // Multiplication by scalar
        constexpr Vec2 operator*(T scalar) const
        {
            return { x * scalar, y * scalar };
        }

        // Division by scalar
        constexpr Vec2 operator/(T scalar) const
        {
            if (scalar == 0)
            {
                throw std::invalid_argument("Division by zero");
            }
            return { x / scalar, y / scalar };
        }

        // Normalize the vector (only for floating point types)
        Vec2 Normalise() const
        {
            static_assert(std::is_floating_point<T>::value, "Normalise is only available for floating point types");
            T mag = Magnitude();
            if (mag == 0)
            {
                throw std::invalid_argument("Cannot normalize a zero vector");
            }
            return { x / mag, y / mag };
        }

        // Calculate the magnitude
        T Magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        // Calculate the square of the magnitude
        T SqrMagnitude() const
        {
            return x * x + y * y;
        }
    };

    using Vec2f = Vec2<float>;
    using Vec2i = Vec2<int>;

} // namespace core

#endif // CORE_MATHS_VEC2_H_
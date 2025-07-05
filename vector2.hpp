#pragma once
#include <cmath>
#include <ostream>

namespace CPL 
{
	template<typename T>

	class Vector2
	{
	public:
		T x;
		T y;

		// Default constructor
		Vector2() :x(0.0f), y(0.0f) {}
		Vector2(T x, T y) : x(x), y(y)	{}

		Vector2(const Vector2& other) : x(other.x), y(other.y) {}
		Vector2 operator=(const Vector2& other)
		{
			if (this != &other)
			{
				x = other.x;
				y = other.y;
			}
			return *this;
		}

		Vector2 operator+(const Vector2& other)
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		static Vector2 ones()
		{
			return Vector2(1.0f, 1.0f);
		}

		static Vector2 zeros()
		{
			return Vector2(0.0f, 0.0f);
		}

		static Vector2 up()
		{
			return Vector2(0.0f, 1.0f);
		}

		bool operator==(const Vector2& other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vector2& other)
		{
			return !(*this == other);
		}

		Vector2 operator*(T scalar)
		{
			return Vector2(x * scalar, y * scalar);
		}

		Vector2 operator/(T scalar)
		{
			return Vector2(x / scalar, y / scalar);
		}

		Vector2 operator*=(T scalar)
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		Vector2 operator/=(T scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		T dot(const Vector2& other) const noexcept
		{
			return x * other.x + y * other.y;
		}

		T cross(const Vector2& other) const noexcept
		{
			return x * other.y - y * other.x;
		}

		T lengthSquared() const noexcept
		{
			return x * x + y * y;
		}

		T length() const noexcept
		{
			return std::sqrt(lengthSquared());
		}

		Vector2 normalized() const noexcept
		{
			T len = length();
			if (len == T(0)) return Vector2(0, 0);
			return Vector2(x / len, y / len);
		}

		void normalize()
		{
			T len = length();
			if (len == T(0)) return;
			x /= len;
			y /= len;
		}

		T angle() const noexcept
		{
			return std::atan2(y, x);
		}

		T angleBetween(const Vector2& other) const noexcept
		{
			T cosTheta = dot(other) / (length() * other.length());
			if (cosTheta > 1)  cosTheta = 1;
			if (cosTheta < -1) cosTheta = -1;
			return std::acos(cosTheta);
		}

		Vector2 direction() const noexcept
		{
			return normalized();
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
		{
			return os << '(' << v.x << ", " << v.y << ')';
		}
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<int> Vector2i;
}
#pragma once
#include <cmath>
#include <ostream>

namespace CPL
{
    template<typename T>
    class Vector3
    {
    public:
        T x, y, z;

        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
        Vector3(const Vector3& other) = default;              // copy-ctor

        Vector3& operator=(const Vector3& other) = default;   // assign

        static Vector3 ones() { return Vector3(1.0f, 1.0f, 1.0f); }
        static Vector3 zeros() { return Vector3(0.0f, 0.0f, 0.0f); }
        static Vector3 up() { return Vector3(0.0f, 1.0f, 0.0f); }

        Vector3 operator+(const Vector3& o) const { return { x + o.x, y + o.y, z + o.z }; }
        Vector3& operator+=(const Vector3& o) { x += o.x; y += o.y; z += o.z; return *this; }

        Vector3 operator*(T s)   const { return { x * s, y * s, z * s }; }
        Vector3& operator*=(T s) { x *= s; y *= s; z *= s; return *this; }

        Vector3 operator/(T s)   const { return { x / s, y / s, z / s }; }
        Vector3& operator/=(T s) { x /= s; y /= s; z /= s; return *this; }

        bool operator==(const Vector3& o) const { return x == o.x && y == o.y && z == o.z; }
        bool operator!=(const Vector3& o) const { return !(*this == o); }

        T dot(const Vector3& o) const { return x * o.x + y * o.y + z * o.z; }

        Vector3 cross(const Vector3& o) const
        {
            return {
                y * o.z - z * o.y,
                z * o.x - x * o.z,
                x * o.y - y * o.x
            };
        }

        T lengthSquared() const { return x * x + y * y + z * z; }
        T length()        const { return std::sqrt(lengthSquared()); }

        Vector3 normalized() const
        {
            T len = length();
            return (len == T(0)) ? Vector3(0, 0, 0) : (*this) / len;
        }
        void normalize()
        {
            T len = length();
            if (len != T(0)) { x /= len; y /= len; z /= len; }
        }

        T angleBetween(const Vector3& o) const
        {
            T c = dot(o) / (length() * o.length());
            if (c > 1) c = 1; if (c < -1) c = -1;
            return std::acos(c);
        }

        friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
        {
            return os << '(' << v.x << ", " << v.y << ", " << v.z << ')';
        }
    };

    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;
}

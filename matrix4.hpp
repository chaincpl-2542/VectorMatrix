#pragma once
#include <array>
#include <ostream>
#include <cmath>

namespace CPL
{
    template<typename T>
    class Matrix4
    {
        std::array<T, 16> m{};

    public:
        Matrix4() { loadIdentity(); }

        Matrix4(std::initializer_list<T> list)
        {
            std::copy(list.begin(), list.end(), m.begin());
        }

        T& operator()(int r, int c) { return m[r * 4 + c]; }
        T  operator()(int r, int c) const { return m[r * 4 + c]; }

        static Matrix4 identity()
        {
            return Matrix4{ 1,0,0,0,
                            0,1,0,0,
                            0,0,1,0,
                            0,0,0,1 };
        }

        static Matrix4 zeros() { return Matrix4{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }; }

        static Matrix4 translate(T tx, T ty, T tz)
        {
            return Matrix4{ 1,0,0,tx,
                            0,1,0,ty,
                            0,0,1,tz,
                            0,0,0,1 };
        }

        static Matrix4 scale(T sx, T sy, T sz)
        {
            return Matrix4{ sx,0 ,0 ,0,
                            0 ,sy,0 ,0,
                            0 ,0 ,sz,0,
                            0 ,0 ,0 ,1 };
        }

        static Matrix4 rotateZ(T rad)
        {
            T c = std::cos(rad), s = std::sin(rad);
            return Matrix4{ c,-s,0,0,
                             s, c,0,0,
                             0, 0,1,0,
                             0, 0,0,1 };
        }

        Matrix4 operator*(const Matrix4& o) const
        {
            Matrix4 r;
            for (int row = 0; row < 4; ++row)
                for (int col = 0; col < 4; ++col)
                {
                    r(row, col) = 0;
                    for (int k = 0; k < 4; ++k)
                        r(row, col) += (*this)(row, k) * o(k, col);
                }
            return r;
        }

        Vector3<T> operator*(const Vector3<T>& v) const
        {
            T x2 = v.x * m[0] + v.y * m[1] + v.z * m[2] + m[3];
            T y2 = v.x * m[4] + v.y * m[5] + v.z * m[6] + m[7];
            T z2 = v.x * m[8] + v.y * m[9] + v.z * m[10] + m[11];
            T w = v.x * m[12] + v.y * m[13] + v.z * m[14] + m[15];
            if (w != T(0) && w != T(1)) { x2 /= w; y2 /= w; z2 /= w; }
            return { x2,y2,z2 };
        }

        void loadIdentity() { *this = identity(); }

        friend std::ostream& operator<<(std::ostream& os, const Matrix4& mat)
        {
            for (int r = 0; r < 4; ++r) {
                os << '|';
                for (int c = 0; c < 4; ++c) os << mat(r, c) << (c < 3 ? ' ' : '|');
                if (r < 3) os << '\n';
            }
            return os;
        }

        static Matrix4 rotateX(T rad)
        {
            T c = std::cos(rad), s = std::sin(rad);
            return Matrix4{
                1, 0, 0, 0,
                0, c,-s, 0,
                0, s, c, 0,
                0, 0, 0, 1 };
        }

        static Matrix4 rotateY(T rad)
        {
            T c = std::cos(rad), s = std::sin(rad);
            return Matrix4{
                 c, 0, s, 0,
                 0, 1, 0, 0,
                -s, 0, c, 0,
                 0, 0, 0, 1 };
        }

        Matrix4 transpose() const
        {
            Matrix4 r;
            for (int rIdx = 0; rIdx < 4; ++rIdx)
                for (int cIdx = 0; cIdx < 4; ++cIdx)
                    r(cIdx, rIdx) = (*this)(rIdx, cIdx);
            return r;
        }

        Matrix4 inverseTRS() const
        {
            Vector3<T> sx{ m[0], m[4], m[8] };
            Vector3<T> sy{ m[1], m[5], m[9] };
            Vector3<T> sz{ m[2], m[6], m[10] };

            T invSX = 1 / sx.length();
            T invSY = 1 / sy.length();
            T invSZ = 1 / sz.length();

            Matrix4 inv;
            inv = this->transpose();
            inv(0, 0) *= invSX; inv(0, 1) *= invSX; inv(0, 2) *= invSX;
            inv(1, 0) *= invSY; inv(1, 1) *= invSY; inv(1, 2) *= invSY;
            inv(2, 0) *= invSZ; inv(2, 1) *= invSZ; inv(2, 2) *= invSZ;

            Vector3<T> t(m[3], m[7], m[11]);
            Vector3<T> tInv = (inv * (t * -1));

            inv(0, 3) = tInv.x; inv(1, 3) = tInv.y; inv(2, 3) = tInv.z;
            inv(3, 0) = inv(3, 1) = inv(3, 2) = 0; inv(3, 3) = 1;
            return inv;
        }

        static Matrix4 perspective(T fovY_rad, T aspect, T near, T far)
        {
            T f = 1 / std::tan(fovY_rad / 2);
            T nf = 1 / (near - far);

            return Matrix4{
                f / aspect, 0, 0,                         0,
                0,        f, 0,                         0,
                0,        0,(far + near) * nf, 2 * far * near * nf,
                0,        0,-1,                         0 };
        }

        static Matrix4 orthographic(T l, T r, T b, T t, T n, T f)
        {
            return Matrix4{
                2 / (r - l),       0,          0, -(r + l) / (r - l),
                      0, 2 / (t - b),          0, -(t + b) / (t - b),
                      0,       0, -2 / (f - n), -(f + n) / (f - n),
                      0,       0,          0,           1 };
        }

        Matrix4 operator*(T s) const
        {
            Matrix4 r;
            for (int i = 0; i < 16; ++i) r.m[i] = m[i] * s;
            return r;
        }
        Matrix4& operator*=(T s)
        {
            for (auto& v : m) v *= s;
            return *this;
        }
    };

    using Matrix4f = Matrix4<float>;
}
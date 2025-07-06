#pragma once
#include "vector3.hpp"
#include "Matrix4.hpp"

namespace CPL {
    struct Transform {
        Vector3f position = Vector3f(0, 0, 0);
        Vector3f rotation = Vector3f(0, 0, 0);
        Vector3f scale = Vector3f(1, 1, 1);

        Matrix4f toMatrix() const {
            return Matrix4f::translate(position.x, position.y, position.z)
                * Matrix4f::rotateZ(rotation.z)
                * Matrix4f::rotateY(rotation.y)
                * Matrix4f::rotateX(rotation.x)
                * Matrix4f::scale(scale.x, scale.y, scale.z);
        }
    };
}
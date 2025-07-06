#include <iostream>
#include <cassert>
#include "vector2.hpp"
#include "vector3.hpp"
#include "Matrix4.hpp"
#include "Transform.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

using namespace CPL;

// ───────────────────────────────────────────
GLFWwindow* init_window(int w, int h)
{
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow* win = glfwCreateWindow(w, h, "CPL", nullptr, nullptr);
    if (!win) { glfwTerminate(); return nullptr; }

    glfwMakeContextCurrent(win);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to init GLEW\n";
        glfwTerminate();
        return nullptr;
    }

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);

    return win;
}

#pragma region Vector 2

// ───────────────────────────────────────────

void t_angle()
{
    Vector2f right(1, 0);
    Vector2f up = Vector2f::up();

    assert(std::abs(right.angle()) < 1e-6);

    assert(std::abs(up.angle() - 1.570796f) < 1e-4);

    assert(std::abs(right.angleBetween(up) - 1.570796f) < 1e-4);

    std::cout << "[Vector2] Angle tests done\n";

}

void t_dot_and_cross()
{
    std::cout << "=====================================" << '\n';

    Vector2f a(3, 4);
    Vector2f b(1, 0);

    float dot = a.dot(b);
    float cross = a.cross(b);

    std::cout << "dot(a,b): " << dot << '\n';
    std::cout << "cross(a,b): " << cross << '\n';

    assert(dot == 3);
    assert(cross == -4);
    std::cout << "[Vector2] Dot and Cross OK\n";
    std::cout << "=====================================" << '\n';

}

void t_length_and_normalize()
{
    std::cout << "=====================================" << '\n';

    Vector2f v(3, 4);
    std::cout << "v.length(): " << v.length() << '\n';
    std::cout << "v.lengthSquared(): " << v.lengthSquared() << '\n';

    Vector2f unit = v.normalized();
    std::cout << "v.normalized(): " << unit << '\n';

    float len = unit.length();
    std::cout << "unit.length(): " << len << '\n';

    v.normalize();
    std::cout << "v after normalize(): " << v << '\n';

    assert(std::abs(len - 1.0f) < 1e-5);
    assert(std::abs(v.length() - 1.0f) < 1e-5);
    std::cout << "[Vector2] Length and Normalize OK\n";
    std::cout << "=====================================" << '\n';

}

void run_vector2_tests()
{
    Vector2f v1(10, 10);
    Vector2f v2;
    v2 = v1;
    assert(v1 == v2);

    Vector2f v3(v1);
    assert(v3 == v1);

    Vector2f v4 = v1 + Vector2f(5, 5);
    assert(v4 == Vector2f(15, 15));

    v4 += Vector2f(5, 5);
    assert(v4 == Vector2f(20, 20));

    Vector2f v5 = v4 * 0.5f;
    assert(v5 == Vector2f(10, 10));

    assert(Vector2f::ones() == Vector2f(1, 1));
    assert(Vector2f::zeros() == Vector2f(0, 0));
    assert(Vector2f::up() == Vector2f(0, 1));

    std::cout << "[Vector2] Tests done\n";

    t_angle();
    t_dot_and_cross();
    t_length_and_normalize();
}

#pragma endregion

#pragma region Vecyot 3

void run_vector3_tests()
{
    Vector3f a(1, 0, 0), b(0, 1, 0);

    assert(a.cross(b) == Vector3f(0, 0, 1));
    assert(a.dot(b) == 0);

    Vector3f c(3, 4, 0);
    assert(c.length() == 5);
    assert(c.normalized().length() - 1.0f < 1e-5);

    Vector3f d = Vector3f::up();
    assert(d == Vector3f(0, 1, 0));

    std::cout << "[Vector3] Tests done\n";
}

#pragma endregion

#pragma region Matrix4
void run_matrix4_projection_tests()
{
    using namespace CPL;
    Matrix4f proj = Matrix4f::perspective(3.14159f / 2, 16 / 9.f, 0.1f, 100.f);
    Vector3f p(0, 0, -0.1f);
    Vector3f clip = proj * p;
    assert(std::abs(clip.z + 1) < 1e-3);
    std::cout << "[Matrix4] projection test ok\n";
}

void run_matrix4_tests()
{
    using namespace CPL;
    Matrix4f mTranslate = Matrix4f::translate(5, 0, 0);
    std::cout << "Translate Matrix:\n" << mTranslate;

    Vector3f p(1, 0, 0);
    Vector3f moved = mTranslate * p;
    assert(moved == Vector3f(6, 0, 0));
    std::cout << "Moved Point: " << moved << '\n';

    Matrix4f mScale = Matrix4f::scale(2, 2, 2);
    assert((mScale * p) == Vector3f(2, 0, 0));

    Matrix4f mRot = Matrix4f::rotateZ(3.14159265f / 2);
    Vector3f up = mRot * Vector3f(1, 0, 0);
    assert(std::abs(up.x) < 1e-4 && std::abs(up.y - 1) < 1e-4);

    std::cout << "[Matrix4] basic tests ok\n";

    run_matrix4_projection_tests();
}

#pragma endregion


// ───────────────────────────────────────────
int main()
{
    glm::vec3 v1(1, 1, 1);
    std::cout << v1.x;

    GLFWwindow* window = init_window(800, 600);
    if (!window) return -1;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Transform t;
        t.position = Vector3f(0.5f, 0.0f, 0.0f);
        t.rotation.z = glfwGetTime();

        Matrix4f modelMatrix = t.toMatrix();

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixf(modelMatrix.data());

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

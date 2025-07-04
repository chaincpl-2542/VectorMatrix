#include <iostream>
#include "vector2.hpp"
#include <cassert>

using namespace CPL;

#pragma region MyRegion
//void v1_must_equal_to_v2() 
//{
//	Vector2f v1(10, 10);
//	Vector2f v2;
//	v2 = v1;
//	assert(v1.x == v2.x && v1.y == v2.y);
//}
//
//void t_copy_constructor()
//{
//	Vector2f v1(10, 10);
//	Vector2f v2(v1);
//	assert(v1.x == v2.x && v1.y == v2.y);
//}
//
//void t_v1_plus_v2()
//{
//	Vector2f v1(10, 10);
//	Vector2f v2(20, 20);
//	Vector2f v3;
//	v3 = v1 + v2;
//	assert(v3.x == 30 && v3.y == 30);
//}
//
//void t_v1_plus_equal_v2()
//{
//	Vector2f v1(10, 15);
//	Vector2f v2(20, 25);
//	Vector2f v3;
//	v1 += v2;
//	assert(v1.x == 30 && v1.y == 40);
//}
//
//
//int main() 
//{
//	v1_must_equal_to_v2();
//	t_copy_constructor();
//	t_v1_plus_v2();
//
//	Vector2<float>::ones(); 
//	Vector2<float>::zeros();
//	Vector2<float>::up();
//
//	return 0;
//}
#pragma endregion

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "CPL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return-1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_TRIANGLES);
		    glColor3f(1.0f, 0.0f, 0.0f);
		    glVertex3f(0.0f, 0.0f, 0.0f);

		    glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);

            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(1.0f, 1.0f, 0.0f);

		glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
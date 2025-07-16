#include <iostream>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "Mesh.hpp"


using namespace std;
using namespace CPL;

const char* vertexShaderSource = R"(
#version 330 core
layout(location = 0) in vec3 aPos; // Vertex position
layout(location = 1) in vec3 aColor; // Vertex color

out vec3 vertexColor; // Output color to the fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0f); // Set the position of the vertex
    vertexColor = aColor; // Pass the color to the fragment shader
}

)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor; // Input color from the vertex shader
out vec4 FragColor; // Output color of the fragment

void main()
{
    FragColor = vec4(vertexColor, 1.0f); // Set the output color with full opacity
}

)";

unsigned int compileShader(unsigned int type, const char* source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	return shader;
}

unsigned int createShaderProgram()
{
	unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	return shaderProgram;
}
// ───────────────────────────────────────────
int main()
{
    if (!glfwInit()) {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Mesh System", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    unsigned int shaderProgram = createShaderProgram();

    Mesh quad = Mesh::CreateQuad();
    Mesh circle = Mesh::CreateCircle();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        quad.Draw();
        circle.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

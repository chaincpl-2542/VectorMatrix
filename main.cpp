#include <iostream>
#include <cassert>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

using namespace std;

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
    GLFWwindow* window;

    if (!glfwInit()) 
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1;
    }
      
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(800, 600, "First  Shader", NULL, NULL);
    if (!window) 
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) 
    {
		cout << "Failed to initialize GLEW" << endl;
		return -1;
    }

	glViewport(0, 0, 800, 600);

    float vertices[] = 
    {
        // position             // colors
		 0.5f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // red
		 0.5f, -0.3f, 0.0f,  0.0f, 1.0f, 0.0f,  // green
		-0.5f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,  // blue
		-0.5f,  0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  // yellow
	};

    unsigned int indices[] =
    {
        0,1,3,
        1,2,3
    };

	unsigned int VAO, VBO, VEO;
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &VEO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int shaderProgram = createShaderProgram();

    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

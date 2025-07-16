#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace CPL
{
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Color;
        glm::vec2 TexCoord;

        Vertex(glm::vec3 pos, glm::vec3 color = glm::vec3(1.0f), glm::vec2 texCoord = glm::vec2(0.0f))
            : Position(pos), Color(color), TexCoord(texCoord) {}
    };

    class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();

        void Draw() const;

        static Mesh CreateTriangle();

        static Mesh CreateQuad(float width = 1.0f, float height = 1.0f);

        static Mesh CreateCircle(float radius = 1.0f, int segments = 32);


    private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
    };
}

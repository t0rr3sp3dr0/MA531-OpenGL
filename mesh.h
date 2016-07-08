//
// Created by lvrma on 05/07/16.
//

#ifndef AVLC_MESH_H
#define AVLC_MESH_H
#include <glm/glm.hpp>
#include <GL/glew.h>

// Lidando com o tipo de dados que vai passar pelo Mesh:
// OpenGL usa coordenadas x,y,z entre -1.0 e 1.0
// O limite inferior da tela é y = -1.0, o topo é 1.0
// O limite esquerdo da tela é x = -1.0, o direito é 1.0
class Vertex{
    public:
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord){
            this->pos = pos; // Definindo a posição do vertice
            this->texCoord = texCoord;
        }
        inline glm::vec3* GetPos() { return &pos; }
        inline glm::vec2* GetTexCoord() { return &texCoord; }
    protected:
    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
};

class Mesh {
    public:
        // Mesh faz uma lista dos vértices dos triângulos a serem desenhados
        Mesh(Vertex* vertices, unsigned int numVertices);
        void Draw(); // Pega o mesh de informações e manda pela Pipeline
        virtual ~Mesh();
    protected:
    private:
        Mesh(const Mesh& other) {}
        void operator=(const Mesh& other) {}

        enum{
            POSITION_VB,
            TEXCOORD_VB,
            NUM_BUFFERS // Quantidade de pedaços de informação no enum
        };

        // vertexArrayObjects são o jeito do openGL se referir a pedaços de informação de Mesh na GPU
        GLuint m_vertexArrayObject; // Pegando uma referencia ao bloco em questão

        // OpenGL se refere a qualquer bloco de dados numa GPU como um Buffer
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];

        unsigned int m_drawCount; // Contando quantos arrayObjects precisaremos desenhar
};


#endif //AVLC_MESH_H

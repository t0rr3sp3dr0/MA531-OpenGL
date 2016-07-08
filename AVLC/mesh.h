//
// Created by lvrma on 05/07/16.
//

#ifndef AVLC_MESH_H
#define AVLC_MESH_H
#include <glm/glm.hpp>
#include <GL/glew.h>

// Dealing with the kind of data that will go through the mesh:
// OpenGL uses x,y,z coordinates between -1.0 and 1.0
// The bottom of the screen is y = -1.0, the top is 1.0
// The left of the screen is x = -1.0, the right is 1.0
class Vertex{
    public:
        Vertex(const glm::vec3& pos, const glm::vec2& texCoord){
            this->pos = pos; // Setting the position for the vertex
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
        // Mesh takes in a list of vertices from the triangles to be drawn
        Mesh(Vertex* vertices, unsigned int numVertices);
        void Draw(); // Take the mesh of data and send it through the pipeline
        virtual ~Mesh();
    protected:
    private:
        Mesh(const Mesh& other) {}
        void operator=(const Mesh& other) {}

        enum{
            POSITION_VB,
            TEXCOORD_VB,
            NUM_BUFFERS // Number of pieces of information in the enum
        };

        // vertexArrayObjects are openGL's way to refer to mesh data on the GPU
        GLuint m_vertexArrayObject; // Getting the handle

        // OpenGL reffers to any block of data on the GPU as a buffer
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];

        unsigned int m_drawCount; // Keeping track of how many arrayObjects we'll need to draw
                                  // In this case, vertices
};


#endif //AVLC_MESH_H

//
// Created by lvrma on 05/07/16.
//

#include "mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices){
    m_drawCount = numVertices; // we'll draw that many objects
    glGenVertexArrays(1, &m_vertexArrayObject); // 1 as in a arrayObject with one vertex
    glBindVertexArray(m_vertexArrayObject); // Any operation that affects a vertex array will affect this one too

    std::vector<glm::vec3> positions; // Vector isolating positional data
    std::vector<glm::vec2> texCoords; // Vector isolating texture positional data

    // Pre-allocating space for the vertices to increase performance
    positions.reserve(numVertices);
    texCoords.reserve(numVertices);

    for(unsigned int i = 0; i < numVertices; i++){
        positions.push_back(*vertices[i].GetPos());
        texCoords.push_back(*vertices[i].GetTexCoord());
    }

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers); // Generates NUM_BUFFERS blocks of data that we can write on

    // Same binding, but we tell openGL to refer to the block of data on position VB as an array
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);

    // Adding the data to the buffer, specifying how big it is (size of one element * n. of elements = size of array)
    // Can't specify the size of the array directly because it's executed at runtime
    // Static Draw means the data will never be modified. That parameter hints on how we'll use the data
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

    // Assigning the buffer's attributes to the GPU. In this case, the Vertex attributes:
    // Since the checking is line per line, all the attributes need to be specified as if it were all a big "list"
    // After all, the data comes in as a stream of bits all in a sequence
    glEnableVertexAttribArray(0); // Tell openGL to read attributes as an array and confirms position 0 exists

    // Position 0, 3 pieces of data (vector 3 = x,y,z), data is float, set normalization to false
    // Needs to skip 0 attributes to get to the next of this type
    // Needs to start at position 0 for the first of this kind
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Same for Texture Coordinates
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1); // Position one
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // 2 pieces of data, X and Y on the 2D texture

    glBindVertexArray(0); // Operations stop affecting any vertex array previously binded

}

Mesh::~Mesh(){
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() { // Bind > Draw > Unbind
    glBindVertexArray(m_vertexArrayObject);

    // Mode (as GL_TRIANGLES) is just the variations of a triangle (including points and lines)
    // start at 0 for the beginning of the array, stop at m_drawCount to draw everything, since it ends there
    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    glBindVertexArray(0);
}
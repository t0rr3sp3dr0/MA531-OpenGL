# version 120
// VERTEX SHADER

// Attributes from the mesh, taking the vector objects from glm

// Vector of 3 components (X, Y, Z) to express the position of the vertex
attribute vec3 position;

attribute vec2 texCoord;

varying vec2 texCoord0;

void main(){

    // Output the vertex in the given position
    // Why vector 4 soon
    gl_Position = vec4(position, 1.0);

    texCoord0 = texCoord;
}


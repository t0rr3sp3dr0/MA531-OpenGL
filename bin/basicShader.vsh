# version 120
// VERTEX SHADER

// Attributes from the mesh, taking the vector objects from glm

// Vector of 3 components (X, Y, Z) to express the position of the vertex
attribute vec3 position;

attribute vec2 texCoord;
varying vec2 texCoord0; // So it can be interpreted in the fragment shader, properly interpolated

// A uniform variable is set by the CPU, and so, as a result of a method in the program,
// can be applied to every pixel
uniform mat4 transform;

void main(){

    // Output the vertex in the given position
    // A vector 4: vector 3 (X,Y,Z) plus a W that means the translation amount.
    // It ranges from 1.0 (a position, 100% translatable) to 0.0 (a direction, not translatable)
    gl_Position = transform * vec4(position, 1.0);

    texCoord0 = texCoord;
}


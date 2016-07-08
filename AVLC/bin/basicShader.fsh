#version 120
// FRAGMENT SHADER

uniform sampler2D diffuse; // A sampler is a way to read texture data

varying vec2 texCoord0; // varying variables are shared

void main(){

    // Outputting the colored pixel
    // In the case of a 4 component vector: Red, Green, Blue, Alpha
    // Values ranging from 0.0 to 1.0 for 0% to 100% e.g. vec4(1.0, 0.0, 0.0, 1.0);

    // Texturing is resolution independent. It ranges from 0.0 to 1.0, bottom left to top right
    gl_FragColor = texture2D(diffuse, texCoord0);
}
# version 120
// VERTEX SHADER

// Atributos do mesh, recebendo objetos vetor do glm:

// Vetor de 3 componentes (X, Y, Z) para expressar a posição do vértice
attribute vec3 position;

attribute vec2 texCoord;
varying vec2 texCoord0; // Assim ele pode ser interpretado e propriamente interpolado para o fragment shader

// Uma variável uniform é definida pela CPU, e assim, como resultado de um método no programa principal,
// pode ser aplicada para cada pixel
uniform mat4 transform;

void main(){

    // Retorna o vértice em certa posição
    // Um vetor 4: vetor 3 (X,Y,Z) mais um W que significa a quantidade de translação
    // Vai desde 1.0 (uma posição, 100% transladável), até 0.0 (uma direção, não transladável)
    gl_Position = transform * vec4(position, 1.0);

    texCoord0 = texCoord;
}


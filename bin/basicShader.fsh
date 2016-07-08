#version 120
// FRAGMENT SHADER

uniform sampler2D diffuse; // Um sampler é uma forma de ler informações de textura

varying vec2 texCoord0; // Variáveis varying são compartilhadas

void main(){

    // Fazendo o output do pixel colorido
    // Neste caso por um vetor de 4 componentes: Red, Green, Blue, Alpha
    // Valores entre 0.0 até 1.0, de 0% a 100%. Ex.: vec4(1.0, 0.0, 0.0, 1.0);

    // Mapear a textura é independente de sua resolução:
    // Variando de 0.0 até 0.1, sendo inferior-esquerdo até superior-direito.
    gl_FragColor = texture2D(diffuse, texCoord0);
}
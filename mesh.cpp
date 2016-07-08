//
// Created by lvrma on 05/07/16.
//

#include "mesh.h"
#include <vector>

Mesh::Mesh(Vertex* vertices, unsigned int numVertices){
    m_drawCount = numVertices; // desenharemos esta quantidade de objetos
    glGenVertexArrays(1, &m_vertexArrayObject); // 1 no sentido de um array object com um vertice
    glBindVertexArray(m_vertexArrayObject); // Qualquer operação que afetar um vertex array também afetará este

    std::vector<glm::vec3> positions; // Isolando as informações posicionais dos vertices
    std::vector<glm::vec2> texCoords; // Isolando as informações posicionais das texturas

    // Pre-alocando espaço somente por questões de performance
    positions.reserve(numVertices);
    texCoords.reserve(numVertices);

    for(unsigned int i = 0; i < numVertices; i++){
        positions.push_back(*vertices[i].GetPos());
        texCoords.push_back(*vertices[i].GetTexCoord());
    }

    // Gerando "NUM_BUFFERS" (valor inteiro) de blocos de dados (Buffers) nos quais podemos escrever
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    // Fazendo binding dos buffers, dizendo ao openGL para se referir como um array ao bloco de dados na posição VB
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);

    // Adicionando dados aos buffers, especificando o seu tamanho
    // (tamanho de um elemento vezes o numero de elementos = tamanho do array)
    // Melhor do que dar o tamanho do array diretamente, pois ele executa em runtime
    // Static Draw significa que não será modificado, indicando como usaremos esse dado
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

    // Determinando os atributos deste buffer na GPU. Neste caso, os atributos do vértice:
    // Já que a checagem é feita linha por linha, todos os atributos precisam ser especificados como se fosse uma lista
    // Afinal os dados vêm em uma grande sequência de bits
    glEnableVertexAttribArray(0); // Fala para o openGL ler como um array e confirma que a posição zero existe

    // Posição 0. Três pedaços de informação (vetor de 3 = x,y,z). Tipo de dado é float. Normalização falsa.
    // Precisa pular 0 atributos para chegar no primeiro deste tipo
    // Precisa começar na posição 0 para o primeiro deste tipo
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Mesma coisa para coordenadas de textura
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1); // Position one
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // 2 pedaços de informação: o X e o Y na textura (que é 2D)

    glBindVertexArray(0); // Com esta linha as operações param de afetar vertices previamentes bindados

}

Mesh::~Mesh(){
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() { // Bind > Draw > Unbind
    glBindVertexArray(m_vertexArrayObject);

    // O modo GL_TRIANGLES indica que serão desenhadas variações de triângulos (incluíndo pontos e linhas)
    // Começa no 0 (indicando começo do array), e para no m_drawCount, que é o fim do array.
    // Assim garantimos que tudo será desenhado.
    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    glBindVertexArray(0);
}
//
// Created by lvrma on 05/07/16.
//

#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName) {
    int width, height, numComponents; // Dados que não são de textura, providenciados pelo stbi
    // Escrevendo os dados da imagem
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

    if (imageData == NULL)
        std::cerr << "Texture: " << fileName << " failed to load" << std::endl;

    // Gerando e fazendo o binding
    glGenTextures(1, &m_texture); // Criando uma textura
    glBindTexture(GL_TEXTURE_2D, m_texture); // Que é 2D

    // Este parâmetro faz um wrap no objeto 3D, repetindo a textura quando ela acaba
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // eixo X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // eixo Y

    // Este parâmetro encolhe ou estica a imagem caso necessário. Neste caso, ele faz por interpolação LINEAR
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Encolhendo
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Esticando (Mag = magnification)

    // Mandando dados para a GPU
    // O Level define a resolução dependendo da camera. Não usarei isto, então está como 0
    // Border também como 0 porque não vou usar e não gosto dela.
    // Formato de dados é RGBA (como definido no display). Os dados do stbi são em unsigned bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData); // Liberando memória
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit) {
    assert(unit >= 0 && unit <= 31); // Garantindo que as texturas não estão fora do range limite do openGL

    // Mudando a textura que o openGL está usando no momento. Ele pode ter muitas texturas ativas.
    glActiveTexture(GL_TEXTURE0 + unit); // Escolhendo a unidade desta textura em questão
    glBindTexture(GL_TEXTURE_2D, m_texture); // Bindando a textura a esta unidade
}


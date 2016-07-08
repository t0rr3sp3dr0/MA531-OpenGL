//
// Created by lvrma on 05/07/16.
//

#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName) {
    int width, height, numComponents; // non-texture data given by stbi
    unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4); // write the data from the image

    if (imageData == NULL)
        std::cerr << "Texture: " << fileName << " failed to load" << std::endl;

    // Generating and binding
    glGenTextures(1, &m_texture); // creating one texture
    glBindTexture(GL_TEXTURE_2D, m_texture); // which is 2D

    // That parameter wraps the 3D object repeating the texture when it ends
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // x axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // y axis

    // That parameter shrinks or stretches the picture if needed. In this case, through LINEAR interpolation
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // shrinking
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // stretching (magnification)

    // Sending to the GPU
    // The level sets the resolution depending on the camera. For now it won't be used, so it's set to 0
    // Border also set to 0 because I don't like it.
    // Data format is RGBA (as defined in display). The data from stbi is in unsigned bytes
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData); // delete the data
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit) {
    assert(unit >= 0 && unit <= 31); // Making sure the textures in openGL don't get out of range

    // Change the current texture openGL is working with. It can have many active textures
    glActiveTexture(GL_TEXTURE0 + unit); // Select this texture's unit
    glBindTexture(GL_TEXTURE_2D, m_texture); // Bind texture to that unit
}


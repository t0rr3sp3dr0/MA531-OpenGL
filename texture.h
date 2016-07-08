//
// Created by lvrma on 05/07/16.
//

#ifndef AVLC_TEXTURE_H
#define AVLC_TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
    public:
        Texture(const std::string& fileName);

        // Binding is the only major thing the texture needs to do
        void Bind(unsigned int unit); // Unit because you can bind up to 32 textures at once

        virtual ~Texture();
    protected:
    private:
        Texture(const Texture& other) {}
        void operator = (const Texture& other) {}

        GLuint m_texture; // handle for the texture
};


#endif //AVLC_TEXTURE_H

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

        // Binding é a principal coisa que uma textura tem que fazer
        void Bind(unsigned int unit); // Uma unidade guia porque se pode bindar até 32 texturas de uma vez

        virtual ~Texture();
    protected:
    private:
        Texture(const Texture& other) {}
        void operator = (const Texture& other) {}

        GLuint m_texture; // Referência para a textura
};


#endif //AVLC_TEXTURE_H

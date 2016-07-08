//
// Created by lvrma on 05/07/16.
//

#ifndef AVLC_SHADER_H
#define AVLC_SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
    public:
        Shader(const std::string& fileName);
        void Bind();
        virtual ~Shader();
    protected:
    private:
        Shader(const Shader& other) {}
        void operator = (const Shader& other) {}

        static const unsigned int NUM_SHADERS = 2; // Could simply create 2 unsigned integers
        // Since we'll only use 2 shaders, but leaving here for future usage in case more are needed.

        GLuint m_program; //OpenGL's handle to refer to the shader program
        GLuint m_shaders[NUM_SHADERS]; // Array with all shaders
};


#endif //AVLC_SHADER_H

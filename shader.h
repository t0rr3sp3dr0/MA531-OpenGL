//
// Created by lvrma on 05/07/16.
//

#ifndef AVLC_SHADER_H
#define AVLC_SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"

class Shader {
    public:
        Shader(const std::string& fileName);
        void Bind();
        void Update(const Transform& transform, const Camera& camera); // Function to update ALL uniforms, can be updated later
        virtual ~Shader();
    protected:
    private:
        Shader(const Shader& other) {}
        void operator = (const Shader& other) {}

        // An enum to store the uniform (constant) variables for the shaders
        enum {
            TRANSFORM_U,

            NUM_UNIFORMS
        };

        static const unsigned int NUM_SHADERS = 2; // Could simply create 2 unsigned integers
        // Since we'll only use 2 shaders, but leaving here for future usage in case more are needed.

        GLuint m_program; //OpenGL's handle to refer to the shader program
        GLuint m_shaders[NUM_SHADERS]; // Array with all shaders
        GLuint m_uniforms[NUM_UNIFORMS]; // Array of openGL handles for each uniform
};


#endif //AVLC_SHADER_H

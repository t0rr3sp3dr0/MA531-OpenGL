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
        void Update(const Transform& transform, const Camera& camera); // Funcao para atualizar TODOS os uniforms
        virtual ~Shader();
    protected:
    private:
        Shader(const Shader& other) {}
        void operator = (const Shader& other) {}

        // Enum para guardar as variaveis uniform (constantes) dos shaders
        enum {
            TRANSFORM_U,

            NUM_UNIFORMS
        };

        static const unsigned int NUM_SHADERS = 2; // Poderia somente criar 2 unsigned integers do GL
        // Mas deixando desta forma mais genérica caso mais shaders forem ser usados no futuro

        GLuint m_program; // Referencia do openGL ao programa em unsigned int
        GLuint m_shaders[NUM_SHADERS]; // Array com todos os shaders
        GLuint m_uniforms[NUM_UNIFORMS]; // Array de referencias unsigned int do openGL para cada uniform
};


#endif //AVLC_SHADER_H

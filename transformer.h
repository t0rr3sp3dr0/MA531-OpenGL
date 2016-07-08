//
// Created by michiles on 08/07/16.
// Edited by lvrma on 08/07/16.
//

#ifndef AVLC_TRANSFORMER_H
#define AVLC_TRANSFORMER_H


#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

class Transformer {

    public:
        static glm::mat4 optimus(glm::vec3 pos) { // Translação
            float x = pos.x;
            float y = pos.y;
            float z = pos.z;

            // Exemplo de como ela é:
            // 1 0 0 X
            // 0 1 0 Y
            // 0 0 1 Z
            // 0 0 0 1

            // Populando a matriz de translação
            float elements[16]; // Primeira linha
            elements[0] = 1;
            elements[1] = 0;
            elements[2] = 0;
            elements[3] = x;

            elements[4] = 0; // Segunda linha
            elements[5] = 1;
            elements[6] = 0;
            elements[7] = y;

            elements[8] = 0; // Terceira linha
            elements[9] = 0;
            elements[10] = 1;
            elements[11] = z;

            elements[12] = 0; // Quarta
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }

        static glm::mat4 bumblebee(float angle) // Rotacionar no eixo X
        {
            // Exemplo de como ela é:
            //      1    0           0       0
            //      0 cos(angle) -sin(angle) 0
            //      0    0           1       0
            //      0    0           0       1

            // Populando a matriz de rotação:
            float elements[16]; // Primeira linha
            elements[0] = 1;
            elements[1] = 0;
            elements[2] = 0;
            elements[3] = 0;

            elements[4] = 0; // Segunda linha
            elements[5] = cosf(angle);
            elements[6] = -sinf(angle);
            elements[7] = 0;

            elements[8] = 0; // Terceira linha
            elements[9] = sinf(angle);
            elements[10] = cosf(angle);
            elements[11] = 0;

            elements[12] = 0; // Quarta linha
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);

        }
        static glm::mat4 meganFox(float angle)  // Rotacionar no eixo Y
        {
            // Exemplo de como ela é:
            //      cos(angle)  0  sin(angle) 0
            //          0       1      0      0
            //      -sin(angle) 0  cos(angle) 0
            //          0       0      0      1

            // Populando a matriz de rotação:
            float elements[16];
            elements[0] = cosf(angle); // Primeira linha
            elements[1] = 0;
            elements[2] = sinf(angle);
            elements[3] = 0;

            elements[4] = 0; // Segunda linha
            elements[5] = 1;
            elements[6] = 0;
            elements[7] = 0;

            elements[8] = -sinf(angle); // Terceira linha
            elements[9] = 0;
            elements[10] = cosf(angle);
            elements[11] = 0;

            elements[12] = 0; // Quarta linha
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }
        static glm::mat4 starscream(float angle) // Rotacionando no eixo Z
        {
            // Exemplo de como ela é:
            //      cos(angle) -sin(angle) 0 0
            //      sin(angle) cos(angle)  0 0
            //          0           0      1 0
            //          0           0      0 1

            // Populando a matriz de rotação:
            float elements[16]; // Primeira linha
            elements[0] = cosf(angle);
            elements[1] = -sinf(angle);
            elements[2] = 0;
            elements[3] = 0;

            elements[4] = sinf(angle); // Segunda linha
            elements[5] = cosf(angle);
            elements[6] = 0;
            elements[7] = 0;

            elements[8] = 0; // Terceira linha
            elements[9] = 0;
            elements[10] = 1;
            elements[11] = 0;

            elements[12] = 0; // Quarta linha
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }
        static glm::mat4 megatron(glm::vec3 vec3)   // Deformação
        {
            float x = vec3.x;
            float y = vec3.y;
            float z = vec3.z;

            // Exemplo de como ela é:
            // X 0 0 0
            // 0 Y 0 0
            // 0 0 Z 0
            // 0 0 0 1

            // Populando a matriz de deformação:
            float elements[16]; // Primeira linha
            elements[0] = x;
            elements[1] = 0;
            elements[2] = 0;
            elements[3] = 0;

            elements[4] = 0; // Segunda linha
            elements[5] = y;
            elements[6] = 0;
            elements[7] = 0;

            elements[8] = 0; // Terceira linha
            elements[9] = 0;
            elements[10] = z;
            elements[11] = 0;

            elements[12] = 0; // Quarta linha
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }

    protected:
    private:
};

#endif //AVLC_TRANSFORMER_H

//
// Created by michiles on 08/07/16.
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
        static glm::mat4 optimus(glm::vec3 pos) { // Translation
            float x = pos.x;
            float y = pos.y;
            float z = pos.z;

            // Example of what it looks like:
            // 1 0 0 X
            // 0 1 0 Y
            // 0 0 1 Z
            // 0 0 0 1

            // Populating the translation matrix:
            float elements[16]; // First row
            elements[0] = 1;
            elements[1] = 0;
            elements[2] = 0;
            elements[3] = x;

            elements[4] = 0; // Second row
            elements[5] = 1;
            elements[6] = 0;
            elements[7] = y;

            elements[8] = 0; // Third row
            elements[9] = 0;
            elements[10] = 1;
            elements[11] = z;

            elements[12] = 0; // Fourth row
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }

        static glm::mat4 bumblebee(float angle) // Rotate X
        {
            // Example of what it looks like:
            //      1    0           0       0
            //      0 cos(angle) -sin(angle) 0
            //      0    0           1       0
            //      0    0           0       1

            // Populating the rotation matrix:
            float elements[16]; // First row
            elements[0] = 1;
            elements[1] = 0;
            elements[2] = 0;
            elements[3] = 0;

            elements[4] = 0; // Second row
            elements[5] = cosf(angle);
            elements[6] = -sinf(angle);
            elements[7] = 0;

            elements[8] = 0; // Third row
            elements[9] = sinf(angle);
            elements[10] = cosf(angle);
            elements[11] = 0;

            elements[12] = 0; // Fourth row
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);

        }
        static glm::mat4 meganFox(float angle)  // Rotate Y
        {
            // Example of what it looks like:
            //      cos(angle)  0  sin(angle) 0
            //          0       1      0      0
            //      -sin(angle) 0  cos(angle) 0
            //          0       0      0      1

            // Populating the rotation matrix:
            float elements[16];
            elements[0] = cosf(angle); // First row
            elements[1] = 0;
            elements[2] = sinf(angle);
            elements[3] = 0;

            elements[4] = 0; // Second row
            elements[5] = 1;
            elements[6] = 0;
            elements[7] = 0;

            elements[8] = -sinf(angle); // Third row
            elements[9] = 0;
            elements[10] = cosf(angle);
            elements[11] = 0;

            elements[12] = 0; // Fourth row
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }
        static glm::mat4 starscream(float angle) // Rotate Z
        {
            // Example of what it looks like:
            //      cos(angle) -sin(angle) 0 0
            //      sin(angle) cos(angle)  0 0
            //          0           0      1 0
            //          0           0      0 1

            // Populating the rotation matrix:
            float elements[16]; // First row
            elements[0] = cosf(angle);
            elements[1] = -sinf(angle);
            elements[2] = 0;
            elements[3] = 0;

            elements[4] = sinf(angle); // Second row
            elements[5] = cosf(angle);
            elements[6] = 0;
            elements[7] = 0;

            elements[8] = 0; // Third row
            elements[9] = 0;
            elements[10] = 1;
            elements[11] = 0;

            elements[12] = 0; // Fourth row
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }
        static glm::mat4 megatron(glm::vec3 vec3)   // Scaling
        {
            float x = vec3.x;
            float y = vec3.y;
            float z = vec3.z;

            // Example of what it looks like:
            // X 0 0 0
            // 0 Y 0 0
            // 0 0 Z 0
            // 0 0 0 1

            // Populating the translation matrix:
            float elements[16]; // First row
            elements[0] = x;
            elements[1] = 0;
            elements[2] = 0;
            elements[3] = 0;

            elements[4] = 0; // Second row
            elements[5] = y;
            elements[6] = 0;
            elements[7] = 0;

            elements[8] = 0; // Third row
            elements[9] = 0;
            elements[10] = z;
            elements[11] = 0;

            elements[12] = 0; // Fourth row
            elements[13] = 0;
            elements[14] = 0;
            elements[15] = 1;

            return glm::make_mat4(elements);
        }

    protected:
    private:
};

#endif //AVLC_TRANSFORMER_H

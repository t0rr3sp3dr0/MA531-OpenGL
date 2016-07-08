//
// Created by michiles on 08/07/16.
//

#ifndef AVLC_MATRIX4_H
#define AVLC_MATRIX4_H


#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>

class Matrix4 {

    public:
        static glm::mat4 translate(glm::vec3 pos) {
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

        static glm::mat3 rotateX(glm::vec3 vec3);
        static glm::mat3 rotateY(glm::vec3 vec3);
        static glm::mat3 rotateZ(glm::vec3 vec3);
        static glm::mat4 deform(glm::vec3 vec3);

    protected:
    private:
};





#endif //AVLC_MATRIX4_H

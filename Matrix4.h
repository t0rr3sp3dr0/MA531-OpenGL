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
    static glm::mat4x4 translate(float x, float y, float z)
    {
        //create and fill the matriz of translation
        float elements[16];
        elements[0] = 1;
        elements[1] = 0;
        elements[2] = 0;
        elements[3] = x;

        elements[4] = 0;
        elements[5] = 1;
        elements[6] = 0;
        elements[7] = y;

        elements[8] = 0;
        elements[9] = 0;
        elements[10] = 1;
        elements[11] = z;

        elements[12] = 0;
        elements[13] = 0;
        elements[14] = 0;
        elements[15] = 1;

        return glm::make_mat4x4(elements);
 }

    glm::mat4x4 rotate(glm::vec3 vec3)
    {



    }

    glm::mat4x4 deformation(glm::vec3 vec3)
    {

    }






};





#endif //AVLC_MATRIX4_H

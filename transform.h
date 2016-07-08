//
// Created by lvrma on 08/07/16.
//

#ifndef AVLC_TRANSFORM_H
#define AVLC_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "transformer.h"

class Transform {
    public:
        // All default to nothing except the scale, which needs to default to 1, otherwise it will be null, not showing
        Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
                m_pos(pos),
                m_rot(rot),
                m_scale(scale) {}

    // A matrix that contains the position, rotation, and scale of something is called the Model (or World) Matrix
    inline glm::mat4 GetModel() const {
        glm::mat4 posMat = Transformer::optimus(m_pos);
        glm::mat4 scaleMat = Transformer::megatron(m_scale);

        glm::mat4 rotX = Transformer::bumblebee(m_rot.x);
        glm::mat4 rotY = Transformer::meganFox(m_rot.y);
        glm::mat4 rotZ = Transformer::starscream(m_rot.z);
        glm::mat4 rotMat = rotX * rotY * rotZ; // Create the final rotation matrix

        return posMat * rotMat * scaleMat;
    }

    inline glm::vec3& GetPos() { return m_pos; }
    inline glm::vec3& GetRot() { return m_rot; }
    inline glm::vec3& GetScale() { return m_scale; }

    inline void SetPos(const glm::vec3& pos) { m_pos = pos; }
    inline void SetRot(const glm::vec3& rot) { m_rot = rot; } // Vector that stores the angles for the rotation
    inline void SetScale(const glm::vec3& scale) { m_scale = scale; }


    protected:
    private:
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scale;
};


#endif //AVLC_TRANSFORM_H

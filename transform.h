//
// Created by lvrma on 08/07/16.
//

#ifndef AVLC_TRANSFORM_H
#define AVLC_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "matrix4.h"

class Transform {
    public:
        // All default to nothing except the scale, which needs to default to 1, otherwise it will be null, not showing
        Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) :
                m_pos(pos),
                m_rot(rot),
                m_scale(scale) {}

    // A matrix that contains the position, rotation, and scale of something is called the Model (or World) Matrix
    inline glm::mat4 GetModel() const {
        glm::mat4 posMat = Matrix4::translate(m_pos);
        glm::mat4 scaleMat = glm::scale(m_scale);
        glm::mat4 rotX = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 rotY = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rotZ = glm::rotate(m_rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 rotMat = rotX * rotY * rotZ; // Create the final rotation matrix

        return posMat * rotMat * scaleMat;
    }

    inline glm::vec3& GetPos() { return m_pos; }
    inline glm::vec3& GetRot() { return m_rot; }
    inline glm::vec3& GetScale() { return m_scale; }

    inline void SetPos(glm::vec3& pos) { m_pos = pos; }
    inline void SetRot(glm::vec3& rot) { m_rot = rot; }
    inline void SetScale(glm::vec3& scale) { m_scale = scale; }


    protected:
    private:
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scale;
};


#endif //AVLC_TRANSFORM_H

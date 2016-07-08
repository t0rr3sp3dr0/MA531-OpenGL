//
// Created by lvrma on 08/07/16.
//

#ifndef AVLC_CAMERA_H
#define AVLC_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
    public:
        // The position, the field of view, the window aspect ratio
        // And the minimum/maximum distance from the camera in which an object can still be displayed
        Camera(const glm::vec3& pos, float fov, float aspect, float minNear, float maxFar){
            // The perspective matrix wasn't manually implemented in the Transformer class because
            // it involves a lot of complicated projection math that we don't understand, so
            // if we were to implement it we would just copy it, which is pointless
            m_perspective = glm::perspective(fov, aspect, minNear, maxFar);
            m_position = pos;
            m_forward = glm::vec3(0,0,1); // Hard-coded this coordinate so the camera faces straight into the screen
            m_up = glm::vec3(0,1,0);      // Hard-coded this coordinate so the camera is upright
        }

        inline glm::mat4 GetViewProjection() const {
            return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
        }
    protected:
    private:
        glm::mat4 m_perspective;
        glm::vec3 m_position;
        glm::vec3 m_forward;
        glm::vec3 m_up;
};

#endif //AVLC_CAMERA_H

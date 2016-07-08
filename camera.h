//
// Created by lvrma on 08/07/16.
//

#ifndef AVLC_CAMERA_H
#define AVLC_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera{
    public:
        // A posição, o campo de visão, o aspect ratio da janela
        // e a distancia mínima/máxima da janela para que o objeto ainda seja desenhado
        Camera(const glm::vec3& pos, float fov, float aspect, float minNear, float maxFar){
            // Não implementei a matriz de perspective manualmente na classe Transformer porque
            // ia envolver muita matemática complexa que não vimos ainda
            // e não faz sentido somente copiar ela no código e pronto, daria na mesma de chamar o GLM
            m_perspective = glm::perspective(fov, aspect, minNear, maxFar);
            m_position = pos;
            m_forward = glm::vec3(0,0,1); // Coordenada fixada para a camera ficar de frente para a tela
            m_up = glm::vec3(0,1,0);      // Coordenada fixada para a camera ficar sempre de cabeça para cima
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

#pragma once
#include <glm/glm.hpp>
#include "Yuzu/Window/Window.h"


namespace Yuzu
{
    class CameraComponent
    {
    public:

        CameraComponent(const glm::vec3& Location, const glm::vec3& Front = glm::vec3(0.0f, 0.0f, -1.0f), const glm::vec3& Up = glm::vec3(0.0f, 1.0f, 0.0f), float FOV = 45.0f)
            :CameraPos(Location), CameraFront(Front), CameraUp(Up), m_yaw(0.0f), m_pitch(0.0f), m_FOV(FOV)
        {

            CameraComponent::Projection = glm::perspective(m_FOV, (float)(Window::Width / Window::Height), 0.1f, 100.0f);

        }
        void Move(const glm::vec3& Direction)
        {
            CameraPos += Direction;
        }



    private:


        glm::vec3 CameraPos;
        glm::vec3 CameraFront;
        glm::vec3 CameraUp;

        double m_LastX;
        double m_LastY;

        float m_pitch;
        float m_yaw;

        float m_speed;
        float m_scrollspeed;
        float m_FOV;



        glm::mat4 Projection;

        friend class CameraHandler;
        float GetFOV() const { return m_FOV; }
        void SetFOV(float FOV) 
        {
            m_FOV = FOV;
            Projection = glm::perspective(m_FOV, (float)(Window::Width / Window::Height), 0.1f, 100.0f); 
        }
        glm::vec3 GetLocation() const { return CameraPos; }






    };
}


#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Yuzu/Window/Window.h"


namespace Yuzu
{
    class CameraComponent
    {
    public:

        CameraComponent(const glm::vec3& Location, const glm::vec3& Front = glm::vec3(0.0f, 0.0f, -1.0f), const glm::vec3& Up = glm::vec3(0.0f, 1.0f, 0.0f), float FOV = 45.0f)
            :CameraPos(Location), CameraFront(Front), CameraUp(Up), m_FOV(FOV)
        {

            CameraComponent::ProjectionMat = glm::perspective(m_FOV, (float)(Window::Width / Window::Height), 0.1f, 100.0f);

        }
        void Move(const glm::vec3& Direction)
        {
            CameraPos += Direction;
        }

        inline glm::vec3 GetLocation() const { return CameraPos; }

        float GetFOV() const { return m_FOV; }
        void SetFOV(float FOV) 
        {
            m_FOV = FOV;
            ProjectionMat = glm::perspective(m_FOV, (float)(Window::Width / Window::Height), 0.1f, 100.0f); 
        }

        void RotateAngle(float angle, const glm::vec3& axis)
        {
            CameraFront = glm::rotate(CameraFront, glm::radians(angle), axis);
        }

        void RotateRadians(float angle, const glm::vec3& axis)
        {
            CameraFront = glm::rotate(CameraFront, angle, axis);
        }
    private:


        glm::vec3 CameraPos;
        glm::vec3 CameraFront;
        glm::vec3 CameraUp;


        float m_FOV;



        glm::mat4 ProjectionMat;
        glm::mat4 ViewMat;
        glm::mat4 ViewProjMat;

        void UpdateMatrices()
        {
            ViewMat = glm::lookAt(CameraPos, (CameraFront + CameraPos), CameraUp);
            ViewProjMat = ProjectionMat * ViewMat;
        }



        friend class CameraHandler;






    };
}


#include "Core.h"

#include "Camera.h"
#include "Window/Window.h"
namespace Yuzu
{

    glm::mat4* Camera::GetProjection()
    {
        return &Projection;
    }
    Camera* Camera::GetCurrentCamera()
    {
        return Camera::ActiveCamera;
    }



    glm::mat4 Camera::Projection;
    Camera* Camera::ActiveCamera;


    Camera::Camera(const glm::vec3& Location, const glm::vec3& Front, const glm::vec3& Up, float speed, float scrollSpeed, float FOV)
        :CameraPos(Location), CameraFront(Front), CameraUp(Up), m_yaw(0.0f), m_pitch(0.0f), m_speed(speed), m_scrollspeed(scrollSpeed), m_FOV(FOV)
    {

        Camera::Projection = glm::perspective(m_FOV, (float)(Window::Width / Window::Height), 0.1f, 100.0f);

    }



    void Camera::Activate() 
    {
        Camera::ActiveCamera = this;
    }

    void Camera::Move(Camera::Movement Direction, float Deltatime)
    {
        float CameraSpeed = m_speed * Deltatime;

        switch (Direction)
        {
        case Camera::Movement::Up:
        {
            CameraPos += CameraSpeed * CameraUp;
            break;
        }
        case Camera::Movement::Down:
        {
            CameraPos -= CameraSpeed * CameraUp;
            break;
        }
        case Camera::Movement::Left:
        {
            CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
            break;
        }
        case Camera::Movement::Right:
        {
            CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * CameraSpeed;
            break;
        }
        case Camera::Movement::Forward:
        {
            CameraPos += CameraSpeed * m_scrollspeed * CameraFront;
            break;
        }
        case Camera::Movement::Back:
        {
            CameraPos -= CameraSpeed * m_scrollspeed * CameraFront;
            break;
        }
        }


    }


    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);
    }
    glm::mat4 Camera::GetViewProjectionMatrix() const
    {
        return  *(GetProjection()) * (glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp));
    }
}
#pragma once


namespace Yuzu
{
	class Camera
	{
	public:
		enum class Movement
		{
			Up, Down, Left, Right, Forward, Back
		};

		static glm::mat4* GetProjection();
		static Camera* GetCurrentCamera();


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



		static glm::mat4 Projection;
		static Camera* ActiveCamera;
	public:

		Camera(const glm::vec3& Location, const glm::vec3& Front, const glm::vec3& Up, float speed, float scrollSpeed = 5.0f, float FOV = 45.0f);

		void Activate();
		void Move(Movement Direction, float Deltatime);
		void RotateHead(double x, double y, bool first);
		float GetFOV() const { return m_FOV; }
		glm::vec3 GetLocation() const { return CameraPos; }
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetViewProjectionMatrix() const;
	};


}
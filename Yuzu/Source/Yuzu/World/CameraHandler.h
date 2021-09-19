#pragma once
#include "Components/CameraComponent.h"



namespace Yuzu
{


	class CameraHandler
	{
	private:
		static CameraComponent* ActiveCamera;


	public:

		static void Activate(CameraComponent* Cam);


		static void Deactivate();
		static glm::vec3 GetCameraLocation();

		static const glm::mat4&  GetViewProjMatrix();

		static void Update();
	};
}


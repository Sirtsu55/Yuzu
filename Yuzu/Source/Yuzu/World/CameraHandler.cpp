#include "Core.h"
#include "CameraHandler.h"


namespace Yuzu
{



		CameraComponent* CameraHandler::ActiveCamera;


		void CameraHandler::Activate(CameraComponent* Cam)
		{
			ActiveCamera = Cam;
		}


		void CameraHandler::Deactivate()
		{
			ActiveCamera = nullptr;
		}

		glm::vec3 CameraHandler::GetCameraLocation()
		{
			if (ActiveCamera)
			{
				return ActiveCamera->CameraPos;
			}
			return glm::vec3(0.0f);
		}
		
		glm::mat4 CameraHandler::GetViewProjMatrix()
		{
			if (ActiveCamera)
			{
				return ActiveCamera->Projection * glm::lookAt(ActiveCamera->CameraPos, (ActiveCamera->CameraFront + ActiveCamera->CameraPos), ActiveCamera->CameraUp);

			}
			return glm::mat4(1.0f);
		}

	
}


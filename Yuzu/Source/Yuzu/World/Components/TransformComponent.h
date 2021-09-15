#pragma once

#include "glm/glm.hpp"
#include "Yuzu/World/CameraHandler.h"

namespace Yuzu
{
	struct TransformComponent
	{
		TransformComponent()
		{
			Transform = glm::mat4(1.0f);

		}
		TransformComponent(const glm::mat4& transform) : Transform(transform) {}

		TransformComponent(const TransformComponent&) = default;
		~TransformComponent() = default;

		glm::mat4 GetMVPTransform() const
		{ 
			return CameraHandler::GetViewProjMatrix() * Transform;
			
		}

		void SetLocation(const glm::vec3& NewLocation)
		{

			Transform[3][0] = NewLocation.x;
			Transform[3][1] = NewLocation.y;
			Transform[3][2] = NewLocation.z;

			
		}
		void TranslateToLocation(const glm::vec3& NewLocation)
		{
			Transform = glm::translate(Transform, NewLocation);

			
		}


		//Sets the Transform by the given scale
		void SetSize(float scale)
		{
			Transform[0][0] = scale;
			Transform[1][1] = scale;
			Transform[2][2] = scale;
		}

		//Sets the Transform by the given scale
		void SetSize(glm::vec3 scale)
		{
			Transform[0][0] = scale.x;
			Transform[1][1] = scale.y;
			Transform[2][2] = scale.x;
		}

		//Adds the Transform by the given scale
		void AddSize(float scale)
		{
			Transform[0][0] += scale;
			Transform[1][1] += scale;
			Transform[2][2] += scale;
		}

		//Adds the Transform by the given scale
		void AddSize(glm::vec3 scale)
		{
			Transform[0][0] += scale.x;
			Transform[1][1] += scale.y;
			Transform[2][2] += scale.x;
		}
		void MulSize(float scale)
		{
			Transform = glm::scale(Transform, glm::vec3(scale));
		}

		//Multiplies the Transform by the given scale
		void MulSize(glm::vec3 scale)
		{
			Transform = glm::scale(Transform, scale);
		}
		
		glm::mat4 Transform;
	};

}
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
			Transform = glm::translate(Transform, NewLocation);
		}

		void SetSize(float scale)
		{
			Transform = glm::scale(Transform, glm::vec3(scale));
		}
		void SetSize(glm::vec3 scale)
		{
			Transform = glm::scale(Transform, scale);
		}
		glm::mat4 Transform;

	};

}
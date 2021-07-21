#pragma once
#include "Rendering/Objects/VertexArray.h"
#include "Rendering/Objects/ElementBuffer.h"
#include "Rendering/Objects/Shader.h"



namespace Yuzu
{

	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexID;
	};
	class Renderer
	{

	public:
		Renderer() = default;
		~Renderer() = default;


		void Draw(const Yuzu::VertexArray& VertArr, const Yuzu::ElementBuffer& ElementBuf, const Yuzu::Shader& Shader) const;
		void Clear() const;

	};





}



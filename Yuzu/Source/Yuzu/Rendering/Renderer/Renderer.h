#pragma once
#include "Yuzu/Rendering/Objects/VertexArray.h"
#include "Yuzu/Rendering/Objects/ElementBuffer.h"
#include "Yuzu/Rendering/Objects/Shader.h"
#include "Yuzu/World/Components/Components.h"
#include "Yuzu/Rendering/Renderer/Lighter.h"

namespace Yuzu
{

	struct PosNormVertex
	{
		glm::vec3 Pos;
		glm::vec3 Normal = glm::vec3(0.0f);
	};

	class Renderer2D
	{
	public:
		struct DefaultPrimitive
		{
			Sptr<CoreShader> CoreShader;
			Uptr<VertexBuffer> VBO;
			Uptr<ElementBuffer> EBO;
			Uptr<VertexArray> VAO;

		};

		struct DefaultTexturedQuad
		{
			Uptr<VertexBuffer> VBO;
			Uptr<ElementBuffer> EBO;
			Uptr<VertexArray> VAO;
		};


	private:
		Renderer2D() = default;
		~Renderer2D() = default;

		static Sptr<CoreShader> Basic2DShader;
		static DefaultPrimitive Square;
		static DefaultPrimitive Triangle;
		static DefaultTexturedQuad TexturedSquare;



	public:
		static void InitializeDefaults();


		static void DrawSprite(TransformComponent& Transform, SpriteComponent& Sprite);

		static void Draw(const Yuzu::VertexArray& VertArr, const Yuzu::ElementBuffer& ElementBuf, const Yuzu::CoreShader& CoreShader);
		static void Clear();



		

		
	};





}



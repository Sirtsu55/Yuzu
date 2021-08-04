#pragma once
#include "Yuzu/Rendering/Objects/VertexArray.h"
#include "Yuzu/Rendering/Objects/ElementBuffer.h"
#include "Yuzu/Rendering/Objects/Shader.h"
#include "Yuzu/World/Components/Components.h"


namespace Yuzu
{


	class Renderer2D
	{
	public:
		struct DefaultPrimitive
		{
			Sptr<Shader> Shader;
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

		static Sptr<Shader> Basic2DShader;
		static DefaultPrimitive Square;
		static DefaultPrimitive Triangle;
		static DefaultTexturedQuad TexturedSquare;

	public:
		static void InitializeDefaults();


		static void DrawSprite(TransformComponent Transform, SpriteComponent Sprite);
		static void DrawSprite(TransformComponent Transform, TexturedSpriteComponent Sprite);

		static void Draw(const Yuzu::VertexArray& VertArr, const Yuzu::ElementBuffer& ElementBuf, const Yuzu::Shader& Shader);
		static void Clear();


		
	};





}



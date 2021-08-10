#pragma once
#include "Yuzu/Rendering/Objects/VertexArray.h"
#include "Yuzu/Rendering/Objects/ElementBuffer.h"
#include "Yuzu/Rendering/Objects/Shader.h"
#include "Yuzu/World/Components/Components.h"
#include "Yuzu/Window/JobHandler.h"

namespace Yuzu
{


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


		static std::queue<Job> OpenGLCalls;

		static void CreateShader(void* Dest);
	public:
		static void InitializeDefaults();
		static void MakeOpenGLCalls();

		static void DrawSprite(TransformComponent Transform, SpriteComponent Sprite);
		static void DrawSprite(TransformComponent Transform, TexturedSpriteComponent Sprite);

		static void Draw(const Yuzu::VertexArray& VertArr, const Yuzu::ElementBuffer& ElementBuf, const Yuzu::CoreShader& CoreShader);
		static void Clear();

		static void QueueShaderCreation(Shader* ShaderDest);


		

		
	};





}



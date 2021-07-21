#pragma once
#include "Rendering/Objects/Shader.h"
#include "Renderer.h"


namespace Yuzu
{

	struct BatchSettings
	{
		unsigned int MaxQuads;
		unsigned int MaxIndices;
		const char* m_ShaderPath;

	};
	struct QuadSettings
	{
		glm::vec3 Posiition;
		float TexID;
		float Size;
		glm::vec4 Color = glm::vec4(0.0f);
	};

	class BatchRenderer
	{

	private:
		
		

		static unsigned int m_VAO;
		static unsigned int m_VBO;
		static unsigned int m_EBO;

		static unsigned int* m_IndicesPtr;

		static Shader* m_Shader;
		static BatchSettings m_Settings;

		static Vertex* m_Vertices;
		static unsigned int m_NumFilled;


	public:
		BatchRenderer() = delete;
		~BatchRenderer() = delete;

		static void Init(const BatchSettings& Settings);
		static void ShutDown();
		
		static void RenderBatch();

		static void InsertQuad(Vertex* NewVertices, unsigned int NumOfVertices);
		static void InsertTexture(Sptr<Yuzu::Texture> NewTexture, int TextureLocation);

		static void CreateQuads(Vertex* Destination, const QuadSettings& Settings);
	};




}
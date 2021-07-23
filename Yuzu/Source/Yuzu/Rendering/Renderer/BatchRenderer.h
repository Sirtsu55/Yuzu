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

	struct VertexID
	{
		Vertex* VertexPtr;
		unsigned int VerticesSize;

		unsigned int* IndexPtr;
		unsigned int IndicesSize;
	};

	/// Position, TextureID, Size, VertexColor
	struct QuadSettings
	{
		glm::vec3 Position;
		float TexID;
		float Size;
		glm::vec4 Color = glm::vec4(0.0f);
	};

	class BatchRenderer
	{

	private:
		
		

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		unsigned int* m_IndicesPtr;
		Vertex* m_VerticesPtr;

		Shader* m_Shader;
		BatchSettings m_Settings;

		unsigned int m_VerticesFilled;
		unsigned int m_IndicesFilled;


	public:
		BatchRenderer(const BatchSettings& Settings);
		~BatchRenderer();
		
		void RenderBatch() const;
	
		
		const VertexID InsertVertices(Vertex* NewVertices, unsigned int NumOfVertices, unsigned int* NewIndices, unsigned int NumOfIndices);
		
		
		/// Change Vertices and also Indices
		void ChangeVertices(const VertexID& Location, Vertex* NewVertices, unsigned int* NewIndices);

		/// Change Vertices only
		void ChangeVertices(const VertexID& Location, Vertex* NewVertices);


		void InsertTexture(Sptr<Yuzu::Texture> NewTexture, int TextureLocation);

		static void CreateQuads(Vertex* Destination, const QuadSettings& Settings);

		void Flush();

	};




}
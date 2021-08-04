#pragma once
#include "Yuzu/Rendering/Objects/Shader.h"


namespace Yuzu
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexID;
	};
	
	

	
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

	class BatchRenderer2D
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
		unsigned int m_IndicesOffset = 0;

	public:
		BatchRenderer2D() = default;
		BatchRenderer2D(const BatchSettings& Settings);
		~BatchRenderer2D();
		
		void RenderBatch() const;
	
		
		const VertexID InsertVertices(Vertex* NewVertices, unsigned int NumOfVertices, unsigned int* NewIndices, unsigned int NumOfIndices);

		
		
		/// Change Vertices and also Indices
		void ChangeVertices(const VertexID& Location, Vertex* NewVertices, unsigned int* NewIndices);

		/// Change Vertices only
		void ChangeVertices(const VertexID& Location, Vertex* NewVertices);

		void ChangeColor(const VertexID& Location, const glm::vec4& NewColor);
	
		void InsertTexture(Sptr<Yuzu::Texture> NewTexture, int TextureLocation);

		static void CreateQuads(Vertex* Destination, const QuadSettings& Settings);

		void CreateIndices(unsigned int* Destination, const unsigned int* IndicesLayout, unsigned int NumOfIndices, unsigned int MaxIndex);

		void Flush();

	};


	

}
#include "Core.h"
#include "BatchRenderer.h"
#include "World/CameraHandler.h"

namespace Yuzu
{
	unsigned int BatchRenderer2D::DefaultQuadIndicesLayout[6] = { 0, 1, 2, 1, 2, 3 };

	BatchRenderer2D::BatchRenderer2D(const BatchSettings& Settings)
	{
		m_Settings = Settings;
		m_Shader = new CoreShader(m_Settings.ShaderPath);

		m_VerticesPtr = new Vertex[m_Settings.MaxVerts];
		m_IndicesPtr = new unsigned int[m_Settings.MaxIndices];

		{
			int Texunits;
			glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &Texunits);
			int* Samplers = new int[Texunits];
			for (int i = 0; i < Texunits; i++)
			{
				Samplers[i] = i;

			}
			m_Shader->Bind();
			int loc = glGetUniformLocation(m_Shader->GetProgram(), "Textures");
			glUniform1iv(loc, Texunits, Samplers);

			delete[] Samplers;
		}


		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, m_Settings.MaxVerts * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

		

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)offsetof(Vertex, Vertex::Position));

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)offsetof(Vertex, Vertex::Color));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)offsetof(Vertex, Vertex::TexCoord));

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)offsetof(Vertex, Vertex::TexID));


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);





		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Settings.MaxIndices * sizeof(unsigned int), m_IndicesPtr, GL_DYNAMIC_DRAW);
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);

		delete[] m_IndicesPtr;
		delete[] m_VerticesPtr;
		delete m_Shader;
	}




	void BatchRenderer2D::ChangeVertices(const VertexID& Location, Vertex* NewVertices, unsigned int* NewIndices)
	{
		memcpy(Location.VertexPtr, NewVertices, Location.VerticesSize);
		memcpy(Location.IndexPtr, NewIndices, Location.IndicesSize);

	}
	void BatchRenderer2D::ChangeVertices(const VertexID& Location, Vertex* NewVertices)
	{
		memcpy(Location.VertexPtr, NewVertices, Location.VerticesSize);

	}

	void BatchRenderer2D::ChangeColor(const VertexID& Location, const glm::vec4& NewColor)
	{
		YZ_PROFILE_FUNCTION();
		int Size = Location.VerticesSize / sizeof(Vertex);
		for (int i = 0; i < Size; i++)
		{
			//Location of the color variables in the Buffer
			char* dest = ((char*)Location.VertexPtr) + offsetof(Vertex, Vertex::Color) + sizeof(Vertex) * i;

			memcpy(dest, glm::value_ptr(NewColor), sizeof(float) * 4);
		}

	}

	const VertexID BatchRenderer2D::InsertVertices(Vertex* NewVertices, unsigned int NumOfVertices, unsigned int* NewIndices, unsigned int NumOfIndices)
	{
		if ( ( (m_VerticesFilled + NumOfVertices) > m_Settings.MaxVerts) || (( m_IndicesFilled + NumOfIndices) > m_Settings.MaxIndices))
		{
			YZC_CRITICAL("Too Many Vertices To Insert LINE:{0}, FILE:{1}", __LINE__, __FILE__);
		}
		else
		{
			memcpy(m_VerticesPtr + m_VerticesFilled, NewVertices, NumOfVertices * sizeof(Vertex));
			memcpy(m_IndicesPtr + m_IndicesFilled, NewIndices, NumOfIndices * sizeof(unsigned int));
		}

		VertexID o_VertexID = { m_VerticesPtr + m_VerticesFilled,
								NumOfVertices * sizeof(Vertex),
								m_IndicesPtr + m_IndicesFilled,
								NumOfIndices * sizeof(unsigned int) };


		m_VerticesFilled += NumOfVertices;
		m_IndicesFilled += NumOfIndices;
		return o_VertexID;
	}

	void BatchRenderer2D::CreateIndices(unsigned int* Destination, const unsigned int* IndicesLayout, unsigned int NumOfIndices, unsigned int MaxIndex)
	{
		
		for (unsigned int i = 0; i < NumOfIndices; i++)
		{
			Destination[i] = IndicesLayout[i] + m_IndicesOffset;
		}
		m_IndicesOffset += MaxIndex;
		
		


	}



	void BatchRenderer2D::CreateQuads(Vertex* Destination, const QuadSettings& Settings)
	{


		
		Destination[0].Position = { Settings.Position.x - Settings.Size, Settings.Position.y - Settings.Size, Settings.Position.z };
		Destination[0].Color = Settings.Color;
		Destination[0].TexCoord = glm::vec2(0.0f);
		Destination[0].TexID = Settings.TexID;

		Destination[1].Position = { Settings.Position.x - Settings.Size, Settings.Position.y + Settings.Size, Settings.Position.z };
		Destination[1].Color = Settings.Color;
		Destination[1].TexCoord = glm::vec2(0.0f, 1.0f);
		Destination[1].TexID = Settings.TexID;

		Destination[2].Position = { Settings.Position.x + Settings.Size, Settings.Position.y - Settings.Size, Settings.Position.z };
		Destination[2].Color = Settings.Color;
		Destination[2].TexCoord = glm::vec2(1.0f, 0.0f);
		Destination[2].TexID = Settings.TexID;


		Destination[3].Position = { Settings.Position.x + Settings.Size, Settings.Position.y + Settings.Size, Settings.Position.z };
		Destination[3].Color = Settings.Color;
		Destination[3].TexCoord = glm::vec2(1.0f);
		Destination[3].TexID = Settings.TexID;
	}

	void BatchRenderer2D::Flush()
	{

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_VerticesFilled * sizeof(Vertex), m_VerticesPtr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_IndicesFilled * sizeof(unsigned int), m_IndicesPtr);

	}

	void BatchRenderer2D::InsertTexture(Sptr<Yuzu::Texture> NewTexture, int TextureLocation)
	{
		m_Shader->InsertTexture(NewTexture, TextureLocation);
		


	}


	void BatchRenderer2D::RenderBatch() const
	{
		m_Shader->Bind();
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		
		
		glm::mat4 MVP = (CameraHandler::GetViewProjMatrix()) * glm::mat4(1.0f);
		m_Shader->SetMat4("MVPMatrix", MVP);
		
		glDrawElements(GL_TRIANGLES, m_Settings.MaxIndices, GL_UNSIGNED_INT, NULL);
		
	}




	

}

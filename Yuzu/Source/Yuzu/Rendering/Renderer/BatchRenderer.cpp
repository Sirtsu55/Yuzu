#include "Core.h"
#include "BatchRenderer.h"
#include "World/Camera.h"
namespace Yuzu
{
	unsigned int BatchRenderer::m_VAO = 0;
	unsigned int BatchRenderer::m_VBO = 0;
	unsigned int BatchRenderer::m_EBO = 0;
	unsigned int BatchRenderer::m_NumFilled = 0;

	unsigned int* BatchRenderer::m_IndicesPtr = nullptr;

	BatchSettings BatchRenderer::m_Settings = {0, 0, 0};
	Shader* BatchRenderer::m_Shader = nullptr;



	void BatchRenderer::Init(const BatchSettings& Settings)
	{


		m_Settings = Settings;
		m_Shader = new Shader("Source/Shaders/TexturedSquare.glsl");

		
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

		glBufferData(GL_ARRAY_BUFFER, m_Settings.MaxQuads * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);
		


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), 0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)(sizeof(float) * 3));

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)(sizeof(float) * 7));

		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (const void*)(sizeof(float) * 9));


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		unsigned int* m_IndicesPtr = new unsigned int[m_Settings.MaxIndices];

		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_Settings.MaxIndices; i += 6)
		{
			m_IndicesPtr[i + 0] =  0 + offset;
			m_IndicesPtr[i + 1] =  1 + offset;
			m_IndicesPtr[i + 2] =  2 + offset;
			m_IndicesPtr[i + 3] =  1 + offset;
			m_IndicesPtr[i + 4] =  2 + offset;
			m_IndicesPtr[i + 5] =  3 + offset;

			offset += 4;
		}
		

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Settings.MaxIndices * sizeof(unsigned int), m_IndicesPtr, GL_STATIC_DRAW);

	}



	void BatchRenderer::ShutDown()
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);

		delete[] m_IndicesPtr;
		delete m_Shader;
	}

	void BatchRenderer::InsertQuad(Vertex* NewVertices, unsigned int NumOfVertices)
	{
		YZ_PROFILE_FUNCTION();
		if (m_VBO)
		{
			void* DataPtr = glMapBufferRange(GL_ARRAY_BUFFER, m_NumFilled * sizeof(Vertex), sizeof(Vertex) * NumOfVertices, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);
			DataPtr = reinterpret_cast<Vertex*>(DataPtr);
			memcpy(DataPtr, NewVertices, NumOfVertices * sizeof(Vertex));

			glUnmapBuffer(GL_ARRAY_BUFFER);


			m_NumFilled += NumOfVertices;
		}



	}

	void BatchRenderer::CreateQuads(Vertex* Destination, const QuadSettings& Settings)
	{


		
		Destination[0].Position = { Settings.Posiition.x - Settings.Size, Settings.Posiition.y - Settings.Size, Settings.Posiition.z };
		Destination[0].Color = Settings.Color;
		Destination[0].TexCoord = glm::vec2(0.0f);
		Destination[0].TexID = Settings.TexID;

		Destination[1].Position = { Settings.Posiition.x - Settings.Size, Settings.Posiition.y + Settings.Size, Settings.Posiition.z };
		Destination[1].Color = Settings.Color;
		Destination[1].TexCoord = glm::vec2(0.0f, 1.0f);
		Destination[1].TexID = Settings.TexID;

		Destination[2].Position = { Settings.Posiition.x + Settings.Size, Settings.Posiition.y - Settings.Size, Settings.Posiition.z };
		Destination[2].Color = Settings.Color;
		Destination[2].TexCoord = glm::vec2(1.0f, 0.0f);
		Destination[2].TexID = Settings.TexID;


		Destination[3].Position = { Settings.Posiition.x + Settings.Size, Settings.Posiition.y + Settings.Size, Settings.Posiition.z };
		Destination[3].Color = Settings.Color;
		Destination[3].TexCoord = glm::vec2(1.0f);
		Destination[3].TexID = Settings.TexID;
	}

	void BatchRenderer::InsertTexture(Sptr<Yuzu::Texture> NewTexture, int TextureLocation)
	{
		m_Shader->InsertTexture(NewTexture.get(), TextureLocation);
		


	}


	void BatchRenderer::RenderBatch()
	{
		m_Shader->Bind();
		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		
		
		glm::mat4 MVP = (Yuzu::Camera::GetCurrentCamera()->GetViewProjectionMatrix()) * glm::mat4(1.0f);
		m_Shader->SetMat4("MVPMatrix", MVP);
		
		glDrawElements(GL_TRIANGLES, m_Settings.MaxIndices, GL_UNSIGNED_INT, NULL);
		
	}




	

}

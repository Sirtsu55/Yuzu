#include "Core.h"
#include "Lighter.h"
#include "glad/glad.h"



namespace Yuzu
{

	unsigned int Lighter::s_MaxLights;
	unsigned int Lighter::s_LightBufferID;
	unsigned int Lighter::s_NumLights;
	bool Lighter::Bound = false;


	void Lighter::_Init(unsigned int MaxLights)
	{

		s_MaxLights = MaxLights;
		glGenBuffers(1, &s_LightBufferID);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_LightBufferID);



		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Light) * s_MaxLights, nullptr, GL_DYNAMIC_DRAW);



	}
	_LightLoc Lighter::InsertLight(const Light& light)
	{
		if (s_NumLights < s_MaxLights)
		{
			glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_LightBufferID);



			int size;
			glGetBufferParameteriv(GL_SHADER_STORAGE_BUFFER, GL_BUFFER_SIZE, &size);

			unsigned int offset = s_NumLights * sizeof(Light);
			unsigned int length = sizeof(Light);
			void* LightBufferPtr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, offset, length, GL_MAP_WRITE_BIT);
			
			if (LightBufferPtr != nullptr)
			{
				memcpy(LightBufferPtr, &light, sizeof(Light));

				s_NumLights++;
			}

			glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
			return { LightBufferPtr };
		}
		YZC_CRITICAL("Lighter: MAX LIGHT LIMIT REACHED");
		__debugbreak();
		return { nullptr };
	}


	void Lighter::UpdateLight(const _LightLoc& Loc, const Light& NewLight)
	{

	}
	void Lighter::DeleteLight(const _LightLoc LigLoc)
	{
		
		
	}
	void Lighter::_Bind()
	{
		Bound = true;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, s_LightBufferID);
	}
}

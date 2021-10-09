#include "Core.h"
#include "Lighter.h"
#include "glad/glad.h"



namespace Yuzu
{

	unsigned int Lighter::s_MaxLights;
	unsigned int Lighter::s_LightBufferID;
	unsigned int Lighter::s_NumLights;
	bool Lighter::Bound = false;
	std::vector<void*> Lighter::s_LightsLoc;

	void Lighter::_Init(unsigned int MaxLights)
	{

		s_MaxLights = MaxLights;
		glGenBuffers(1, &s_LightBufferID);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_LightBufferID);


		glNamedBufferData(s_LightBufferID, sizeof(Light) * s_MaxLights, nullptr, GL_DYNAMIC_DRAW);

		s_LightsLoc.reserve(s_MaxLights);


	}
	LightID Lighter::InsertLight(const Light& light)
	{
		if (s_NumLights < s_MaxLights)
		{

			unsigned int offset = s_NumLights * sizeof(Light);
			unsigned int length = sizeof(Light);
			void* LightBufferPtr = glMapNamedBufferRange(s_LightBufferID, offset, length, GL_MAP_WRITE_BIT);



			if (LightBufferPtr != nullptr)
			{
				memcpy(LightBufferPtr, &light, sizeof(Light));

				s_NumLights++;
				s_LightsLoc.push_back(LightBufferPtr);

				glUnmapNamedBuffer(s_LightBufferID);

				// Location of the Light in the array
				return { static_cast<int>(s_LightsLoc.size()) - 1 };
			}

			glUnmapNamedBuffer(s_LightBufferID);

			return { -1 };

		}
		YZC_CRITICAL("Lighter: MAX LIGHT LIMIT REACHED");
		__debugbreak();
		return { -1 };
	}


	void Lighter::UpdateLight(const LightID& Loc, const Light& NewLight)
	{

		if (Loc.LightAdress != -1 && s_LightsLoc[Loc.LightAdress] != nullptr)
		{
			glMapNamedBuffer(s_LightBufferID, GL_WRITE_ONLY);

			memcpy(s_LightsLoc[Loc.LightAdress], &NewLight, sizeof(Light));

			glUnmapNamedBuffer(s_LightBufferID);
		}
	}


	void Lighter::DeleteLight(const LightID& Loc)
	{
		
		
		glMapNamedBuffer(s_LightBufferID, GL_WRITE_ONLY);

		int LightsAhead = s_LightsLoc.size() - (Loc.LightAdress + 1);


		

		if (LightsAhead > 0)
		{
			memcpy(s_LightsLoc[Loc.LightAdress], s_LightsLoc[Loc.LightAdress + 1], sizeof(Light) * LightsAhead);
		}

		for (int i = Loc.LightAdress + 1; i < s_LightsLoc.size(); i++)
		{
			void* newDest = static_cast<void*>((char*)s_LightsLoc[i] - sizeof(Light));
			s_LightsLoc[i] = newDest;
		}

		s_LightsLoc[Loc.LightAdress] = nullptr;

		s_NumLights--;
		glUnmapNamedBuffer(s_LightBufferID);

	}
	void Lighter::_Bind()
	{
		Bound = true;
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, s_LightBufferID);
	}
}

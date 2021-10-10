#pragma once

namespace Yuzu
{

	//struct Light
	//{
	//	glm::vec3 Color = glm::vec3(1.0f);
	//	float AmbientIntensity = 0.1f;
	//	glm::vec3 Position;
	//	float Intensity = 1.0f;

	//	
	//};
	struct Light
	{
		glm::vec3 LightColor = glm::vec3(1.0f);
		float AmbientIntensity = 0.2f;

		glm::vec3 Position;
		float Radius = 1.0f;

		
		


		float SpecularIntensity = 1.0f;
		float Power = 1.0f;

		
	};

	struct LightID
	{
		int LightAdress;
	};


	class Lighter
	{

		
	public:

		static void _Init(unsigned int MaxLights);

		static LightID InsertLight(const Light& light);

		static void UpdateLight(const LightID& Loc, const Light& NewLight);

		static void DeleteLight(const LightID& LigLoc);

		static void _Bind();

	private:

		static unsigned int s_MaxLights;
		static unsigned int s_LightBufferID;
		static unsigned int s_NumLights;
		static bool Bound;
		
		static std::vector<void*> s_LightsLoc;
		
		friend class Renderer2D;

	};

}
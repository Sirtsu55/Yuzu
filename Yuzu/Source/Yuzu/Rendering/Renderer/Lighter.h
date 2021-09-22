#pragma once

namespace Yuzu
{

	struct Light
	{
		glm::vec3 Color;
		float Radius;
		glm::vec3 Position;
		float Intensity;
	};

	struct _LightLoc
	{
		const void* LightAdress;
	};


	class Lighter
	{

		
	public:

		static void _Init(unsigned int MaxLights);

		static _LightLoc InsertLight(const Light& light);

		static void UpdateLight(const _LightLoc& Loc, const Light& NewLight);

		static void DeleteLight(const _LightLoc LigLoc);

		static void _Bind();

	private:

		static unsigned int s_MaxLights;
		static unsigned int s_LightBufferID;
		static unsigned int s_NumLights;
		static bool Bound;
		
		friend class Renderer2D;

	};

}
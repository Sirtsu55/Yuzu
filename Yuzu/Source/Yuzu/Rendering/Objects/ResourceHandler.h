#pragma once
#include "Window/JobHandler.h"


namespace Yuzu
{
	class ResourceHandler
	{
	private:
		

	public:
		static void CreateShader(Shader& Settings);
		static JobHandler ResourceThread;
	
	};
}

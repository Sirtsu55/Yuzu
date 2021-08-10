#include "Core.h"
#include "ResourceHandler.h"
#include "Rendering/Renderer/Renderer.h"


namespace Yuzu
{
	JobHandler ResourceHandler::ResourceThread;


	void ResourceHandler::CreateShader(Shader& Dest)
	{
		Dest.Src = CoreShader::ParseShader(Dest.Path);

		Renderer2D::QueueShaderCreation(&Dest);
	}


}

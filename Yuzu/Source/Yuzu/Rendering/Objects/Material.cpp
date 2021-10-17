#include "Core.h"
#include "Material.h"

namespace Yuzu
{


	Material::Material(const MaterialSettings& Settings, const std::string& ShaderPath)
		:MatShader(CreateSptr<CoreShader>(ShaderPath))
	{
		MatShader->Bind();
		SetColor(Settings.Color);
		SetAmbient(Settings.Ambient);
		SetDiffuse(Settings.Diffuse);
		SetShine(Settings.Shine);
		SetSpecular(Settings.Specular);
	}

	Material::Material()
	{
	}

	Material::~Material()
	{
	}

	void Material::SetColor(const glm::vec4& Color)
	{
		if (MatShader != nullptr)
		{
			MatShader->SetVec4("Mat.Color", Color);
		}
	}

	void Material::SetDiffuse(const glm::vec3& Diff)
	{
		if (MatShader != nullptr)
		{
			MatShader->SetVec3("Mat.Diffuse", Diff);
		}

	}

	void Material::SetAmbient(const glm::vec3& Amb)
	{
		if (MatShader != nullptr)
		{
			MatShader->SetVec3("Mat.Ambient", Amb);
		}
	}

	void Material::SetSpecular(const glm::vec3& Spec)
	{
		if (MatShader != nullptr)
		{
			MatShader->SetVec3("Mat.Specular", Spec);
		}
	}

	void Material::SetShine(const float Shine)
	{
		if (MatShader != nullptr)
		{
			MatShader->SetFloat("Mat.Shinienss", Shine);
		}
	}


}

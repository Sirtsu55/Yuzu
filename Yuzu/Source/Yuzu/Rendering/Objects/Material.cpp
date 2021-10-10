#include "Core.h"
#include "Material.h"

namespace Yuzu
{






	Material::Material(const glm::vec3& Diffuse, const glm::vec3& Ambient, const glm::vec3& Specular, float Shine)
	{
	}
	Material(const glm::vec3& Diffuse, const glm::vec3& Ambient, const glm::vec3& Specular, float Shine, const std::string& ShaderPath)
	{
	}

	Material::~Material()
	{
	}

	void Material::SetColor(const glm::vec3& Color)
	{
		Sdr->SetVec3("Material.Color", Color);
	}

	void Material::SetDiffuse(const glm::vec3& Diff)
	{
		Sdr->SetVec3("Material.Color", Color);

	}

	void Material::SetAmbient(const glm::vec3& Amb)
	{
		Sdr->SetVec3("Material.Color", Color);
	}

	void Material::SetSpecular(const glm::vec3& Spec)
	{
		Sdr->SetVec3("Material.Color", Color);
	}

	void Material::SetShine(const glm::vec3& Shine)
	{
		Sdr->SetVec3("Material.Color", Color);
	}


}
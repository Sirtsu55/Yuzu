#pragma once
#include "Shader.h"



namespace Yuzu
{


	class Material
	{

	public:

		Material(
			const glm::vec3& Diffuse = glm::vec3(1.0f), const glm::vec3& Ambient = glm::vec3(0.2f),
			const glm::vec3& Specular = glm::vec3(), float Shine = 32.0f;
		);
		Material(
			const glm::vec3& Diffuse = glm::vec3(1.0f), const glm::vec3& Ambient = glm::vec3(0.2f),
			const glm::vec3& Specular = glm::vec3(), float Shine = 32.0f, const std:string& ShaderPath);
		);

		~Material();
		Material(const Material&) = default;




	private:

		Sptr<Yuzu::CoreShader> Sdr = nullptr;



		void SetColor(const glm::vec3& Color);
		void SetDiffuse(const glm::vec3& Diff);
		void SetAmbient(const glm::vec3& Amb);
		void SetSpecular(const glm::vec3& Spec);
		void SetShine(const glm::vec3& Shine);


		glm::vec3 Diffuse;
		glm::vec3 Ambient;
		glm::vec3 Specular;
		float Shininess;
	};
}

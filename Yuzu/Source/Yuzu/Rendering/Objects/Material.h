#pragma once



namespace Yuzu
{

	struct MaterialSettings
	{
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec3 Diffuse = glm::vec3(1.0f);
		glm::vec3 Ambient = glm::vec3(0.2f);
		glm::vec3 Specular = glm::vec3(1.0f);
		float Shine = 32.0f;

	};
	class Material
	{

	public:

		Material(const MaterialSettings& Settings, const std::string& ShaderPath);
		Material();
		~Material();
		

		void SetColor(const glm::vec4& Color);
		void SetDiffuse(const glm::vec3& Diff);
		void SetAmbient(const glm::vec3& Amb);
		void SetSpecular(const glm::vec3& Spec);
		void SetShine(const float Shine);




	private:





		Sptr<CoreShader> MatShader;
		glm::vec3 Diffuse;
		glm::vec3 Ambient;
		glm::vec3 Specular;
		float Shininess;


		friend class Renderer2D;
	};
}

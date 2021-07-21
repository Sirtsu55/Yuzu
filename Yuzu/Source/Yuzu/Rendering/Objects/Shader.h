#pragma once
#include "Core.h"

#include <unordered_map>

#include "Texture.h"

namespace Yuzu
{
	struct ShaderSource
	{
		std::string VertexShource;
		std::string FragmentShource;
	};

	class Shader
	{

	private:

		unsigned int m_ProgramID;
		std::string m_FilePath;


		unsigned int CreateShader(const std::string VertexSource, std::string FragmentSource);
		ShaderSource ParseShader();
		unsigned int CompileShader(unsigned int type, const std::string& source);

		mutable std::unordered_map<std::string, int> m_UniformMap;
		std::unordered_map<unsigned char, Yuzu::Texture*> m_TextureMap;



	public:
		Shader(const std::string& filepath);
		Shader();
		~Shader();

		unsigned int GetProgram() { return m_ProgramID; }
		void Bind() const;

		void SetInt(const char* name, int val) const;
		void SetVec4(const char* name, const glm::vec4& value) const;
		void SetVec3(const char* name, const glm::vec3& value) const;
		void SetMat4(const char* name, const glm::mat4& matrix) const;
		int GetUniformLocation(const char* name) const;

		void InsertTexture(Yuzu::Texture* NewTex, unsigned char slot);
	};

}
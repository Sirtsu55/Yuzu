#pragma once
#include "Core.h"

#include <unordered_map>

#include "Texture.h"

namespace Yuzu
{
	struct ShaderSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};
	class CoreShader
	{

	private:

		unsigned int m_ProgramID;


		unsigned int CreateShader(const std::string VertexSource, std::string FragmentSource);
		unsigned int CompileShader(unsigned int type, const std::string& source);

		mutable std::unordered_map<std::string, int> m_UniformMap;
		std::unordered_map<unsigned char, Sptr<Yuzu::Texture>> m_TextureMap;



	public:
		CoreShader(const std::string& filepath);
		CoreShader(const ShaderSource& Source);
		CoreShader();
		~CoreShader();

		unsigned int GetProgram() { return m_ProgramID; }
		void Bind() const;

		void SetInt(const char* name, int val) const;
		void SetVec4(const char* name, const glm::vec4& value) const;
		void SetVec3(const char* name, const glm::vec3& value) const;
		void SetMat4(const char* name, const glm::mat4& matrix) const;
		void SetMat3(const char* name, const glm::mat3& matrix) const;
		int GetUniformLocation(const char* name) const;

		void InsertTexture(Sptr<Texture> NewTex, unsigned char slot);


		static ShaderSource ParseShader(std::string Path);
	};
	struct Shader
	{
		std::string Path;
		ShaderSource Src;
		Sptr<CoreShader> shader;
	};


}
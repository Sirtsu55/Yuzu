#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#define FMT_HEADER_ONLY
#include "fmt/format.h"


enum class ShaderType : char
{
	SpriteShader = 1, TexturedSpriteShader = 2, BatchRendererShader = 3
};
ShaderType GetInputShaderType()
{
	int SdrType;
	std::cin >> SdrType;
	return (ShaderType)SdrType;

}

std::string GetInputString(const char* output = "")
{

	if (output)
	{
		std::cout << output << "\n";
	}
	std::string Inp;
	std::cin >> Inp;
	return Inp;

}



std::string ShaderTypeToString(ShaderType SdrTyp)
{
	switch (SdrTyp)
	{
		case ShaderType::SpriteShader:
		{
			return std::string("SpriteShader");
			break;
		}
		case ShaderType::TexturedSpriteShader:
		{
			return std::string("TexturedSpriteShader");
			break;
		}
		case ShaderType::BatchRendererShader:
		{
			return std::string("BatchRendererShader");
			break;
		}
	}
	return std::string();
}

int main()
{
	std::string UserFunc;

	ShaderType SdrType;

	std::cout << "Welcome to Yuzu Shader Creator!\n ----------------\n";
	std::cout << "Choose A Shader Type\n1.Sprite Shader\n2.Textured SpriteShader\n3.Batch Renderer Shader\n";
	SdrType = GetInputShaderType();

	std::cout << "Function Name?\n";

	std::string FuncName = GetInputString();
	
	std::string FilePath = fmt::format("ShaderTemplates/{0}.glsl", ShaderTypeToString(SdrType));
	std::fstream ShaderFile(FilePath);


	std::stringstream ShaderSrc;
	std::string srcLine;

	while (std::getline(ShaderFile, srcLine))
	{
		if (srcLine.size() > 1)
		{
			ShaderSrc << fmt::format(srcLine.c_str(), FuncName.c_str()) << "\n";
		}
		else
		{
			ShaderSrc << srcLine << "\n";
		}
		
	}

	ShaderFile.close();


	std::string FileName = GetInputString("Shader File Name?");

	std::ofstream OutFile(fmt::format("GeneratedShaders/{}.glsl", FileName));
	
	if (OutFile.is_open())
	{
		OutFile << ShaderSrc.str().c_str();
		OutFile.close();
	}

	std::cout << fmt::format("New Shader Should Be In GeneratedShaders/{}.glsl", FileName);
	GetInputString();
}
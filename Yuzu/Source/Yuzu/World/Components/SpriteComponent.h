#pragma once


namespace Yuzu
{
	enum class PrimitiveShape
	{
		Square, Triangle
	};

	struct SpriteComponent
	{



		SpriteComponent() = default;
		SpriteComponent(const glm::vec4& color, PrimitiveShape shape) : Color(color), ShapeType(shape) {}
		SpriteComponent(const SpriteComponent&) = default;
		~SpriteComponent() = default;

		glm::vec4 Color = { 1.0f, 1.0f, 1.0f , 1.0f };
		PrimitiveShape ShapeType;
	};

	//TO DO: ADD this to rendering

	struct TexturedSpriteComponent
	{

		TexturedSpriteComponent() = default;
		TexturedSpriteComponent(const std::string path)
			: SpriteShader(CreateSptr<Yuzu::CoreShader>(path))
		{
			
		}


		TexturedSpriteComponent(const TexturedSpriteComponent&) = default;
		~TexturedSpriteComponent() = default;
		

		void InsertTexture(Sptr<Texture> Texture, int slot)
		{
			SpriteShader->Bind();
			SpriteShader->InsertTexture(Texture, slot);
			std::string name = "Image" + std::to_string(slot);
			SpriteShader->SetInt(name.c_str(), slot);
		}
		Sptr<CoreShader> SpriteShader;

	};
}
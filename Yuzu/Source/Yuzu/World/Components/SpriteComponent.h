#pragma once


namespace Yuzu
{
	enum class PrimitiveShape : char
	{
		Square, Triangle, Invalid
	};

	struct SpriteComponent
	{



		SpriteComponent() = default;
		SpriteComponent(const glm::vec4& color, PrimitiveShape shape) : Color(color), ShapeType(shape), Textured(false) {}
		SpriteComponent(const std::string path, bool Texed = false) 
			: SpriteShader(CreateSptr<Yuzu::CoreShader>(path)), Textured(Texed) {}

		SpriteComponent(const SpriteComponent&) = default;
		~SpriteComponent() = default;


		void Hide()
		{
			Color.a = 0.0f;
			Visible = false;
		}
		void Show()
		{
			Color.a = 1.0f;
			Visible = true;
		}

		operator bool() const
		{
			if (Textured)
			{
				return SpriteShader == nullptr ? false : true;
			}
			else
			{
				return ShapeType == PrimitiveShape::Invalid ? false : true;
			}
		}

		void InsertTexture(Sptr<Texture> Texture, int slot)
		{
			if (Textured)
			{
				SpriteShader->Bind();
				SpriteShader->InsertTexture(Texture, slot);
				std::string name = "Image" + std::to_string(slot);
				SpriteShader->SetInt(name.c_str(), slot);
			}
		}

		bool Visible = true;
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f , 1.0f };
		PrimitiveShape ShapeType = PrimitiveShape::Invalid;
		Sptr<CoreShader> SpriteShader = nullptr;
		bool Textured;
	private:
	
	};

	


}
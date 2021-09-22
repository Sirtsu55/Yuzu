#pragma once


namespace Yuzu
{
	enum class Shape : char
	{
		Square, Triangle, CustomSquare, CustomTriangle, Textured, Invalid
	};

	struct SpriteComponent
	{



		SpriteComponent() = default;
		SpriteComponent(const glm::vec4& color, Shape shape) : Color(color), ShapeType(shape) {}
		SpriteComponent(const std::string path, Shape shape) 
			: SpriteShader(CreateSptr<Yuzu::CoreShader>(path)), ShapeType(shape){}

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
			if (ShapeType == Shape::Textured || ShapeType == Shape::CustomSquare || ShapeType == Shape::CustomSquare)
			{
				return SpriteShader == nullptr ? false : true;
			}
			else
			{
				return ShapeType == Shape::Invalid ? false : true;
			}
		}

		void InsertTexture(Sptr<Texture> Texture, int slot)
		{
			if (ShapeType == Shape::Textured)
			{
				SpriteShader->Bind();
				SpriteShader->InsertTexture(Texture, slot);
				std::string name = "Image" + std::to_string(slot);
				SpriteShader->SetInt(name.c_str(), slot);
			}
		}

		
		bool Visible = true;
		glm::vec4 Color = { 1.0f, 1.0f, 1.0f , 1.0f };
		Shape ShapeType = Shape::Invalid;
		Sptr<CoreShader> SpriteShader = nullptr;
	private:
	
	};

	


}
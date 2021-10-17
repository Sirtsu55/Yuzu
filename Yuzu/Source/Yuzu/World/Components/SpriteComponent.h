#pragma once
#include "Yuzu/Rendering/Objects/Material.h"


namespace Yuzu
{
	enum class Shape : char
	{
		Square, Triangle, CustomSquare, CustomTriangle, Textured, Invalid
	};

	struct SpriteComponent
	{



		SpriteComponent() = default;
		SpriteComponent(Shape shape, const MaterialSettings& MatSettings) : ShapeType(shape), SpriteMat(MatSettings, "Resources/Shaders/Basic2D.glsl") {}
		SpriteComponent(Shape shape, const MaterialSettings& MatSettings, const std::string& path)
			: ShapeType(shape), SpriteMat(MatSettings, path)
		{
		}

		SpriteComponent(const SpriteComponent&) = default;
		~SpriteComponent() = default;



		operator bool() const
		{

			return ShapeType == Shape::Invalid ? false : true;
			
		}

		void InsertTexture(Sptr<Texture> Texture, int slot)
		{
			if (ShapeType == Shape::Textured)
			{

			}

			else
			{
				YZC_INFO("SpriteType Not Shape::Textured");
			}
		}

		
		bool Visible = true;
		Shape ShapeType = Shape::Invalid;

		Material SpriteMat;
	private:
	
	};

	


}
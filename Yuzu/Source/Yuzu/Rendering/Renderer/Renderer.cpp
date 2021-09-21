#include "Core.h"
#include "Renderer.h"
#include "Lighter.h"

namespace Yuzu
{	


	void Renderer2D::Draw(const Yuzu::VertexArray& VertArr, const Yuzu::ElementBuffer& ElementBuf, const Yuzu::CoreShader& CoreShader)
	{
		CoreShader.Bind();
		VertArr.Bind();
		ElementBuf.Bind();

		glDrawElements(GL_TRIANGLES, ElementBuf.GetCount(), ElementBuf.GetDataType(), NULL);
		
	}

	

	void Renderer2D::DrawSprite(TransformComponent Transform, SpriteComponent Sprite)
	{
		if (!Lighter::Bound)
		{

		}

		if (Sprite.Textured)
		{
			Sprite.SpriteShader->Bind();
			Sprite.SpriteShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
			Square.CoreShader->SetInt("NumLights", Lighter::s_NumLights);
			TexturedSquare.VAO->Bind();
			TexturedSquare.EBO->Bind();
			glDrawElements(GL_TRIANGLES, Square.EBO->GetCount(), Square.EBO->GetDataType(), NULL);
		}
		else
		{

			switch (Sprite.ShapeType)
			{
				case PrimitiveShape::Square:
				{

					Square.CoreShader->Bind();
					Square.CoreShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
					Square.CoreShader->SetVec4("iColor", Sprite.Color);
					Square.CoreShader->SetInt("NumLights", Lighter::s_NumLights);
					Square.VAO->Bind();
					Square.EBO->Bind();
					glDrawElements(GL_TRIANGLES, Square.EBO->GetCount(), Square.EBO->GetDataType(), NULL);
					break;
				}
				case PrimitiveShape::Triangle:
				{
					Triangle.CoreShader->Bind();
					Triangle.CoreShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
					Triangle.CoreShader->SetVec4("iColor", Sprite.Color);
					Triangle.CoreShader->SetInt("NumLights", Lighter::s_NumLights);
					Triangle.VAO->Bind();
					Triangle.EBO->Bind();
					glDrawElements(GL_TRIANGLES, Triangle.EBO->GetCount(), Triangle.EBO->GetDataType(), NULL);
					break;

					break;
				}

				default:
					break;
			}


		}
	}




	void Renderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}











	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//----------------------INITIALIZATION OF PRIMITIVES---------------------------
	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------

	Sptr<CoreShader> Renderer2D::Basic2DShader;
	Renderer2D::DefaultPrimitive Renderer2D::Square;
	Renderer2D::DefaultPrimitive Renderer2D::Triangle;
	Renderer2D::DefaultTexturedQuad Renderer2D::TexturedSquare;
		



	void Renderer2D::InitializeDefaults()
	{
		float TriangleVertices[] = { -0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f };
		unsigned char TriangleIndices[] = {0, 1, 2};
		float SquareVertices[] = { -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f };
		unsigned char SquareIndices[] = { 0, 1, 2, 1, 2, 3 };

		VertexBufferLayout PrimitiveLayout;
		PrimitiveLayout.Push<float>(3);



		Basic2DShader = CreateSptr<CoreShader>("Resources/Shaders/Basic2D.glsl");


		Triangle.CoreShader = Basic2DShader;
		Triangle.VAO = CreateUptr<VertexArray>();
		Triangle.VBO = CreateUptr<VertexBuffer>(PtrToArr(TriangleVertices), (unsigned int)sizeof(TriangleVertices), GL_STATIC_DRAW);
		Triangle.EBO = CreateUptr<ElementBuffer>(TriangleIndices, 3, GL_STATIC_DRAW, GL_UNSIGNED_BYTE);
		Triangle.VAO->AddBuffer(*(Triangle.VBO.get()), PrimitiveLayout);


		Square.CoreShader = Basic2DShader;
		Square.VAO = CreateUptr<VertexArray>();
		Square.VBO = CreateUptr<VertexBuffer>(PtrToArr(SquareVertices), (unsigned int)sizeof(SquareVertices), GL_STATIC_DRAW);
		Square.EBO = CreateUptr<ElementBuffer>(SquareIndices, 6, GL_STATIC_DRAW, GL_UNSIGNED_BYTE);

		Square.VAO->AddBuffer(*(Square.VBO.get()), PrimitiveLayout);




		float TexturedSquareVertices[] = { 
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f , 1.0f, 1.0f
		};

		PrimitiveLayout.Push<float>(2);

		TexturedSquare.VAO = CreateUptr<VertexArray>();
		TexturedSquare.VBO = CreateUptr<VertexBuffer>(PtrToArr(TexturedSquareVertices), (unsigned int)sizeof(TexturedSquareVertices), GL_STATIC_DRAW);
		TexturedSquare.EBO = CreateUptr<ElementBuffer>(SquareIndices, 6, GL_STATIC_DRAW, GL_UNSIGNED_BYTE);
		TexturedSquare.VAO->AddBuffer(*(TexturedSquare.VBO.get()), PrimitiveLayout);




		
		

	}




}
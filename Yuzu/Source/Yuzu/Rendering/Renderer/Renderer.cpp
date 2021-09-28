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

	

	void Renderer2D::DrawSprite(TransformComponent& Transform, SpriteComponent& Sprite)
	{
		if (!Lighter::Bound)
		{
			Lighter::_Bind();
		}


		glm::mat3 NormMat = glm::transpose(glm::inverse(Transform.Transform * CameraHandler::GetViewMatrix()));

		switch (Sprite.ShapeType)
		{
			case Shape::Square:
			{

				Square.CoreShader->Bind();
				Square.CoreShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
				Square.CoreShader->SetMat4("ModelMatrix", Transform.Transform);
				Square.CoreShader->SetMat3("NormalMatrix", NormMat);
				Square.CoreShader->SetUnsignedInt("NumberOfLights", Lighter::s_NumLights);
				Square.CoreShader->SetVec4("iColor", Sprite.Color);
				Square.CoreShader->SetVec3("CameraPos", CameraHandler::GetCameraLocation());

				Square.VAO->Bind();
				Square.EBO->Bind();
				glDrawElements(GL_TRIANGLES, Square.EBO->GetCount(), Square.EBO->GetDataType(), NULL);
				break;
			}
			case Shape::Triangle:
			{
				Triangle.CoreShader->Bind();
				Triangle.CoreShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
				Triangle.CoreShader->SetMat4("ModelMatrix", Transform.Transform);
				Triangle.CoreShader->SetMat3("NormalMatrix", NormMat);
				Triangle.CoreShader->SetUnsignedInt("NumberOfLights", Lighter::s_NumLights);
				Triangle.CoreShader->SetVec3("CameraPos", CameraHandler::GetCameraLocation());

				Triangle.CoreShader->SetVec4("iColor", Sprite.Color);
				Triangle.VAO->Bind();
				Triangle.EBO->Bind();
				glDrawElements(GL_TRIANGLES, Triangle.EBO->GetCount(), Triangle.EBO->GetDataType(), NULL);
				break;

					
			case Shape::Textured:
			{
				Sprite.SpriteShader->Bind();
				Sprite.SpriteShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
				Sprite.SpriteShader->SetMat4("ModelMatrix", Transform.Transform);
				Sprite.SpriteShader->SetMat3("NormalMatrix", NormMat);
				Sprite.SpriteShader->SetUnsignedInt("NumberOfLights", Lighter::s_NumLights);
				Sprite.SpriteShader->SetVec3("CameraPos", CameraHandler::GetCameraLocation());

				TexturedSquare.VAO->Bind();
				TexturedSquare.EBO->Bind();
				glDrawElements(GL_TRIANGLES, Square.EBO->GetCount(), Square.EBO->GetDataType(), NULL);
				break;

			}
			case Shape::CustomSquare:
			{
				Sprite.SpriteShader->Bind();
				Sprite.SpriteShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
				Sprite.SpriteShader->SetMat4("ModelMatrix", Transform.Transform);
				Sprite.SpriteShader->SetMat3("NormalMatrix", NormMat);
				Sprite.SpriteShader->SetVec4("iColor", Sprite.Color);
				Sprite.SpriteShader->SetUnsignedInt("NumberOfLights", Lighter::s_NumLights);
				Sprite.SpriteShader->SetVec3("CameraPos", CameraHandler::GetCameraLocation());

				Square.VAO->Bind();
				Square.EBO->Bind();
				glDrawElements(GL_TRIANGLES, Square.EBO->GetCount(), Square.EBO->GetDataType(), NULL);
				break;
			}
			case Shape::CustomTriangle:
			{
				Sprite.SpriteShader->Bind();
				Sprite.SpriteShader->SetMat4("MVPMatrix", Transform.GetMVPTransform());
				Sprite.SpriteShader->SetMat4("ModelMatrix", Transform.Transform);
				Sprite.SpriteShader->SetMat3("NormalMatrix", NormMat);
				Sprite.SpriteShader->SetVec4("iColor", Sprite.Color);
				Sprite.SpriteShader->SetUnsignedInt("NumberOfLights", Lighter::s_NumLights);
				Sprite.SpriteShader->SetVec3("CameraPos", CameraHandler::GetCameraLocation());


				Triangle.VAO->Bind();
				Triangle.EBO->Bind();
				glDrawElements(GL_TRIANGLES, Triangle.EBO->GetCount(), Triangle.EBO->GetDataType(), NULL);
				break;

			}

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





		PosNormVertex TriangleVertices[] = 
		{	{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(0.0f, 0.5f, 0.0f),   glm::vec3(0.0f, 0.0f, 1.0f) },
			{ glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f) }
		};
		unsigned char TriangleIndices[] = {0, 1, 2};


		PosNormVertex SquareVertices[] = 
		{ 
			 {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)},
			 {glm::vec3(-0.5f, 0.5f, 0.0f ), glm::vec3(0.0f, 0.0f, 1.0f)},
			 {glm::vec3(0.5f, -0.5f, 0.0f ), glm::vec3(0.0f, 0.0f, 1.0f)},
			 {glm::vec3(0.5f, 0.5f, 0.0f  ), glm::vec3(0.0f, 0.0f, 1.0f)}
		};
		unsigned char SquareIndices[] = { 0, 1, 2, 1, 2, 3 };

		VertexBufferLayout PrimitiveLayout;
		PrimitiveLayout.Push<float>(3);
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
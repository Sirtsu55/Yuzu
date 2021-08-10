#include "MyEntity.h"




MyEntity::MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape)
	:TagEntity(World, "Mario")
{
	AddComponent<Yuzu::TransformComponent>();

	AddComponent<Yuzu::TickComponent>(this);
	Yuzu::InputComponent& Inputs = AddComponent<Yuzu::InputComponent>(this, 10);
	Yuzu::CameraComponent& Camera = AddComponent<Yuzu::CameraComponent>(glm::vec3(0.0f, 0.0f, 5.0f));
	Yuzu::CameraHandler::Activate(&Camera);
	
	
	m_Name = GetPtrToComponent<Yuzu::TagComponent>();
	m_Camera = GetPtrToComponent<Yuzu::CameraComponent>();
	Inputs.AddKeybind(Yuzu::InputKey::Space, Entity_Function(MyEntity::LoadGibby));
	Inputs.AddKeybind(Yuzu::InputKey::W, Entity_Function(MyEntity::MoveUp));
	Inputs.AddKeybind(Yuzu::InputKey::S, Entity_Function(MyEntity::MoveDown));
	Inputs.AddKeybind(Yuzu::InputKey::A, Entity_Function(MyEntity::MoveLeft));
	Inputs.AddKeybind(Yuzu::InputKey::D, Entity_Function(MyEntity::MoveRight));
}



void MyEntity::Update(float DeltaTime)
{
	YZA_INFO(m_Name->Name);

	


}
void MyEntity::LoadGibby()
{

	if (!(HasComponent<Yuzu::TexturedSpriteComponent>()))
	{
		auto TexComp = AddComponent<Yuzu::TexturedSpriteComponent>("Resources/Shaders/TexturedBasic2D.glsl");
		Sptr<Yuzu::Texture> Tex = CreateSptr<Yuzu::Texture>("Resources/image.jpg");
		TexComp.InsertTexture(Tex, 0);
	}
	
	YZA_CRITICAL("TEXTURE ADDED");
}

void MyEntity::MoveUp()
{
	m_Camera->Move(glm::vec3(0.0f, 1.0f, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
}

void MyEntity::MoveDown()
{
	m_Camera->Move(glm::vec3(0.0f, -1.0f, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
}

void MyEntity::MoveLeft()
{
	m_Camera->Move(glm::vec3(-1.0f, 0.0f, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
}

void MyEntity::MoveRight()
{
	m_Camera->Move(glm::vec3(1.0f, 0.0f, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
}


void MyEntity::Clicked()
{
	YZA_CRITICAL("RIGHT CLICK");

}



MyEntity::~MyEntity()
{
}





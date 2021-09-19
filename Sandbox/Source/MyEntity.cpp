#include "MyEntity.h"


Sptr<Yuzu::Texture> MyEntity::s_Texture = nullptr;

MyEntity::MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape)
	:TagEntity(World, "Mario")
{
	AddComponent<Yuzu::TransformComponent>();

	AddComponent<Yuzu::TickComponent>(this);
	AddComponent<Yuzu::SpriteComponent>("Resources/Shaders/TexturedBasic2D.glsl");
	
	Sptr<Yuzu::Texture> Tex = CreateSptr<Yuzu::Texture>("Resources/SpaceShip.png");
	
	Yuzu::InputComponent& Inputs = AddComponent<Yuzu::InputComponent>(this, 10);
	Yuzu::CameraComponent& Camera = AddComponent<Yuzu::CameraComponent>(glm::vec3(0.0f, 0.0f, 5.0f));
	Yuzu::CameraHandler::Activate(&Camera);
	
	m_Name = GetPtrToComponent<Yuzu::TagComponent>();
	m_Camera = GetPtrToComponent<Yuzu::CameraComponent>();
	m_SpriteComp = GetPtrToComponent<Yuzu::SpriteComponent>();
	m_InputComp = GetPtrToComponent<Yuzu::InputComponent>();
	m_TransComp = GetPtrToComponent<Yuzu::TransformComponent>();
	
	m_SpriteComp->InsertTexture(Tex, 0);

	Inputs.AddContinuousKeybind(Yuzu::InputKey::W, Entity_Keybind(MyEntity::MoveUp));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::S, Entity_Keybind(MyEntity::MoveDown));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::A, Entity_Keybind(MyEntity::MoveLeft));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::D, Entity_Keybind(MyEntity::MoveRight));
	Inputs.AddKeybind(Yuzu::InputKey::MouseButtonLeft, Entity_Keybind(MyEntity::ScaleTriangle));
	Inputs.AddKeybind(Yuzu::InputKey::Space, Entity_Keybind(MyEntity::SpawnSquare));


	Yuzu::CreateFunctionTimer<MyEntity>(1.0f, this, &MyEntity::ScaleSlow);
	
}



void MyEntity::Update(float DeltaTime)
{
	glm::vec3 CLoc = m_Camera->GetLocation();
	CLoc.z -= 5.0f;
	m_TransComp->SetLocation(CLoc);

	m_InputComp->UpdateContinuousKeys();
}



void MyEntity::ScaleTriangle(Yuzu::KeyState State)
{

}

void MyEntity::SpawnSquare(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed)
	{
		glm::vec3 SpawnLoc = m_Camera->GetLocation();
		SpawnLoc.z -= 5.0f;
		
	}
}

bool MyEntity::ScaleSlow()
{

	
	
	
	m_TransComp->MulSize(1.5f);
	

	return true;
}



void MyEntity::MoveUp(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed || State == Yuzu::KeyState::Repeated)
	{
		m_Camera->Move(glm::vec3(0.0f, m_Speed, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
	}
}

void MyEntity::MoveDown(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed || State == Yuzu::KeyState::Repeated)
	{
		m_Camera->Move(glm::vec3(0.0f, -m_Speed, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
	}
}
void MyEntity::MoveLeft(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed || State == Yuzu::KeyState::Repeated)
	{
		m_Camera->Move(glm::vec3(-m_Speed, 0.0f, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
	}
}

void MyEntity::MoveRight(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed || State == Yuzu::KeyState::Repeated)
	{
		m_Camera->Move(glm::vec3(m_Speed, 0.0f, 0.0f) * Yuzu::World::GetTimeStep().Seconds);
	}
}






MyEntity::~MyEntity()
{
}





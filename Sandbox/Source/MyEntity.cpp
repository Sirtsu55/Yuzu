#include "MyEntity.h"


Sptr<Yuzu::Texture> MyEntity::s_Texture = nullptr;

MyEntity::MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape)
	:TagEntity(World, "Mario")
{
	AddComponent<Yuzu::TransformComponent>();

	AddComponent<Yuzu::TickComponent>(this);
	AddComponent<Yuzu::SpriteComponent>(glm::vec4(0.76f, 0.1f, 0.1f, 1.0f), Yuzu::PrimitiveShape::Triangle);

	
	Yuzu::InputComponent& Inputs = AddComponent<Yuzu::InputComponent>(this, 10);
	Yuzu::CameraComponent& Camera = AddComponent<Yuzu::CameraComponent>(glm::vec3(0.0f, 0.0f, 5.0f));
	Yuzu::CameraHandler::Activate(&Camera);
	
	
	m_Name = GetPtrToComponent<Yuzu::TagComponent>();
	m_Camera = GetPtrToComponent<Yuzu::CameraComponent>();
	m_SpriteComp = GetPtrToComponent<Yuzu::SpriteComponent>();
	m_InputComp = GetPtrToComponent<Yuzu::InputComponent>();
	m_TransComp = GetPtrToComponent<Yuzu::TransformComponent>();
	
	m_TransComp->SetSize(glm::vec3(1.0f, 2.0f, 1.0f));


	Inputs.AddContinuousKeybind(Yuzu::InputKey::W, Entity_Keybind(MyEntity::MoveUp));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::S, Entity_Keybind(MyEntity::MoveDown));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::A, Entity_Keybind(MyEntity::MoveLeft));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::D, Entity_Keybind(MyEntity::MoveRight));
	Inputs.AddKeybind(Yuzu::InputKey::Space, Entity_Keybind(MyEntity::Jump));
}



void MyEntity::Update(float DeltaTime)
{

	
	m_InputComp->UpdateContinuousKeys();
}



void MyEntity::Jump(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed)
	{
		Yuzu::CreateFunctionTimer<MyEntity>(1.0f, this, &MyEntity::ScaleSlow);
	}
}

bool MyEntity::ScaleSlow()
{
	m_Scale +=  Yuzu::World::GetTimeStep().Seconds;
	if (m_Scale > 4.0f)
	{
		return false;
	}
	YZA_CRITICAL(m_Scale);
	m_TransComp->SetSize(1.0f + Yuzu::World::GetTimeStep().Seconds);
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





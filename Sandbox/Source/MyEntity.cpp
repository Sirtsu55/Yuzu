#include "MyEntity.h"


Sptr<Yuzu::Texture> MyEntity::s_Texture = nullptr;

MyEntity::MyEntity(Yuzu::World* World)
	:TagEntity(World, "Mario"), sq(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.3f, 0.0f))
{
	AddComponent<Yuzu::TransformComponent>();

	AddComponent<Yuzu::TickComponent>(this);
	Yuzu::MaterialSettings Mset;

	AddComponent<Yuzu::SpriteComponent>(Yuzu::Shape::CustomSquare, Mset);
	
	
	Yuzu::InputComponent& Inputs = AddComponent<Yuzu::InputComponent>(this, 10);
	Yuzu::CameraComponent& Camera = AddComponent<Yuzu::CameraComponent>(glm::vec3(0.0f, 0.0f, 10.0f));
	Yuzu::CameraHandler::Activate(&Camera);
	
	m_Name = GetPtrToComponent<Yuzu::TagComponent>();
	m_Camera = GetPtrToComponent<Yuzu::CameraComponent>();
	m_SpriteComp = GetPtrToComponent<Yuzu::SpriteComponent>();
	m_InputComp = GetPtrToComponent<Yuzu::InputComponent>();
	m_TransComp = GetPtrToComponent<Yuzu::TransformComponent>();
	m_TransComp->SetSize(3.0f);
	


	Inputs.AddContinuousKeybind(Yuzu::InputKey::W, Entity_Keybind(MyEntity::MoveUp));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::S, Entity_Keybind(MyEntity::MoveDown));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::A, Entity_Keybind(MyEntity::MoveLeft));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::D, Entity_Keybind(MyEntity::MoveRight));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::Z, Entity_Keybind(MyEntity::RotateLeft));
	Inputs.AddContinuousKeybind(Yuzu::InputKey::X, Entity_Keybind(MyEntity::RotateRight));

	Yuzu::Light Lig1;
	Yuzu::Light Lig2;

	Lig1.Position = glm::vec3(10.0f, 0.0f, 1.1f);
	Lig1.Power = 50.0f;
	Lig1.AmbientIntensity = 0.2f;


	Lig2.Position = glm::vec3(-5.0f, 0.0f, 1.1f);
	Lig2.Power = 50.0f;
	Lig2.AmbientIntensity = 0.2f;

	Lig = Yuzu::Lighter::InsertLight(Lig1);
	
}



void MyEntity::Update(float DeltaTime)
{

	//m_TransComp->RotateAngle(DeltaTime * 100, glm::vec3(0.0f, 1.0f, 0.0f));
	//m_Camera->RotateAngle(DeltaTime * 100, glm::vec3(0.0f, 1.0f, 0.0f));

	//glm::vec3 loc = m_Camera->GetLocation() - glm::vec3(0.0f, 0.0f, 10.0f);

	//m_TransComp->SetLocation(loc);


	//Yuzu::Light Light;

	//Light.Position = m_Camera->GetLocation();
	//Light.Intensity = 200.0f;
	//Light.AmbientIntensity = 0.2f;
	//
	//Yuzu::Lighter::UpdateLight(Lig, Light);
	m_InputComp->UpdateContinuousKeys();
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

void MyEntity::RotateLeft(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed || State == Yuzu::KeyState::Repeated)
	{
		m_Camera->RotateAngle(Yuzu::World::GetTimeStep().Milliseconds * 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
void MyEntity::RotateRight(Yuzu::KeyState State)
{
	if (State == Yuzu::KeyState::Pressed || State == Yuzu::KeyState::Repeated)
	{
		m_Camera->RotateAngle(-Yuzu::World::GetTimeStep().Milliseconds * 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
}




MyEntity::~MyEntity()
{
}





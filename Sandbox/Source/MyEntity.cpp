#include "MyEntity.h"




MyEntity::MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape)
	:Entity(World)
{
	AddComponent<Yuzu::TransformComponent>();
	auto TexComp = AddComponent<Yuzu::TexturedSpriteComponent>("Resources/Shaders/TexturedBasic2D.glsl", Shape);
	Sptr<Yuzu::Texture> Tex = CreateSptr<Yuzu::Texture>("Resources/image.jpg");
	TexComp.InsertTexture(Tex, 0);

	AddComponent<Yuzu::TickComponent>(this);
	Yuzu::InputComponent& Inputs = AddComponent<Yuzu::InputComponent>(this);

	
	Inputs.AddKeybind(Yuzu::InputKey::W, Entity_Function(MyEntity::OnWPressed));
	Inputs.AddMouseBind(Yuzu::MouseButton::ButtonLeft, Entity_Function(MyEntity::Clicked));
}

void MyEntity::Update(float DeltaTime)
{
	YZA_INFO("MYENTITY UPDATED");

}

void MyEntity::OnWPressed()
{
}
void MyEntity::Clicked()
{
}



MyEntity::~MyEntity()
{
}





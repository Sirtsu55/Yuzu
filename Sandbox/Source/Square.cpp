#include "Square.h"



Square::Square(glm::vec3 location, glm::vec3 color)
	: Entity(Yuzu::World::GetWorld())
{
	AddComponent<Yuzu::TransformComponent>();
	GetComponent<Yuzu::TransformComponent>().SetLocation(location);
	AddComponent<Yuzu::SpriteComponent>(glm::vec4(color, 1.0f), Yuzu::PrimitiveShape::Square);


}

Square::~Square()
{
}

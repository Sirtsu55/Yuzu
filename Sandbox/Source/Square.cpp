#include "Square.h"



Square::Square(const glm::vec3& location, const glm::vec3& color)
	: Entity(Yuzu::World::GetWorld())
{
	AddComponent<Yuzu::TransformComponent>().SetLocation(location);

	AddComponent<Yuzu::SpriteComponent>("Resources/Shaders/Triangle.glsl", Yuzu::Shape::CustomSquare).Color = glm::vec4(color,1.0f);

	GetComponent<Yuzu::TransformComponent>().AddSize(2.0f);

}

Square::~Square()
{
}

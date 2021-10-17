#include "Square.h"



Square::Square(const glm::vec3& location, const glm::vec3& color)
	: Entity(Yuzu::World::GetWorld())
{
	AddComponent<Yuzu::TransformComponent>().SetLocation(location);
	Yuzu::MaterialSettings mat;

	mat.Color = glm::vec4(color, 1.0f);
	AddComponent<Yuzu::SpriteComponent>(Yuzu::Shape::CustomSquare, mat);

	GetComponent<Yuzu::TransformComponent>().AddSize(2.0f);

}

Square::~Square()
{
}

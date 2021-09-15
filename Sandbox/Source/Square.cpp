#include "Square.h"



Square::Square(glm::vec3 location)
{
	AddComponent<Yuzu::SpriteComponent>(glm::vec4(0.76f, 0.1f, 0.1f, 1.0f), Yuzu::PrimitiveShape::Square);


}

#include "Projectile.h"

Projectile::Projectile(glm::vec3 Location)
	:Entity(Yuzu::World::GetWorld())
{
	AddComponent<Yuzu::SpriteComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), Yuzu::Shape::Square);
	AddComponent<Yuzu::TransformComponent>();
	AddComponent<Yuzu::TickComponent>(this);

	m_Trans = GetPtrToComponent<Yuzu::TransformComponent>();

	m_Trans->SetSize(glm::vec3(0.25, 2.0f, 1.0f));
	m_Trans->MulSize(0.25f);
	m_Trans->SetLocation(Location);

}

Projectile::~Projectile()
{


}

void Projectile::Update(float Deltatime)
{
	m_Trans->TranslateToLocation(glm::vec3(0.0f, 10.0f * Deltatime, 0.0f ));
	m_AliveTime += Deltatime;
	if (m_AliveTime > 1.0f)
	{
		this->~Projectile();
	}
	
}

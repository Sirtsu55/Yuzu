#pragma once
#include "Yuzu.h"
class Projectile : public Yuzu::Entity
{


public:
	Projectile(glm::vec3 Location);
	~Projectile();
	void Update(float Deltatime) override;

private:

	Yuzu::TransformComponent* m_Trans;
	float m_AliveTime = 0.0f;
};


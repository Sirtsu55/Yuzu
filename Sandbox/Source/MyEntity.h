#pragma once

#include "Yuzu.h"


class MyEntity : public Yuzu::Entity
{


public:


	MyEntity() = default;
	~MyEntity();
	MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape);

	void Update(float DeltaTime) override;

	void OnWPressed();
	void Clicked();
private:



};


#pragma once

#include "Yuzu.h"
#include "Yuzu/World/Entities/TagEntity.h"

class MyEntity : public Yuzu::TagEntity
{


public:


	MyEntity() = default;
	~MyEntity();
	MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape);

	void Update(float DeltaTime) override;

	void LoadGibby();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Clicked();


private:
	Yuzu::TagComponent* m_Name;
	Yuzu::CameraComponent* m_Camera;



};


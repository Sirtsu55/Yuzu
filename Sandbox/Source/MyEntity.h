#pragma once

#include "Yuzu.h"
#include "Yuzu/World/Entities/TagEntity.h"
#include "Square.h"


class MyEntity : public Yuzu::TagEntity
{


public:


	MyEntity() = default;
	~MyEntity();
	MyEntity(Yuzu::World* World, Yuzu::PrimitiveShape Shape);

	void Update(float DeltaTime) override;

	void MoveUp(Yuzu::KeyState State);
	void MoveDown(Yuzu::KeyState State);
	void MoveLeft(Yuzu::KeyState State);
	void MoveRight(Yuzu::KeyState State);
	void ScaleTriangle(Yuzu::KeyState State);
	void SpawnSquare(Yuzu::KeyState State);
	bool ScaleSlow();
private:
	Yuzu::TagComponent* m_Name;
	Yuzu::CameraComponent* m_Camera;
	Yuzu::SpriteComponent* m_SpriteComp;
	Yuzu::InputComponent* m_InputComp;
	Yuzu::TransformComponent* m_TransComp;
	static Sptr<Yuzu::Texture> s_Texture;
	bool m_Showed = false;
	float m_Speed = 4.0f;
	float m_JumpSpeed = 0.0f;
	float m_Scale = 2.0f;

	std::vector<Uptr<Square>> m_Squares;
};


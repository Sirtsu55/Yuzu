#pragma once
#include "Yuzu.h"
#include "MyEntity.h"
class SandboxApp : public Yuzu::Application
{
public:
	SandboxApp();
	~SandboxApp();

	void Run() override;
	void OnUpdate(float DeltaTime) override;
	void OnWidgetRender(float Deltatime) override;

	void OnDestroy() override;

	//MyEntity m_Square = MyEntity();
	Yuzu::BatchRenderer2D* m_BRenderer;
	Yuzu::VertexID m_ChunkID;
	glm::vec4 m_ChunkColor = glm::vec4(1.0f);
private:
	Sptr<Yuzu::Window> m_Window;
	Sptr<Yuzu::World> m_World;
	
};





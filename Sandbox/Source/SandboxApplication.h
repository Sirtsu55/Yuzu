#pragma once
#include "Yuzu.h"
#include "MyEntity.h"
class SandboxApp : public Yuzu::Application
{
public:

	void Init() override;
	void Start() override;
	void OnUpdate(float DeltaTime) override;
	void OnWidgetRender(float Deltatime) override;

	void OnDestroy() override;

	//MyEntity m_Square = MyEntity();
private:
	Sptr<Yuzu::Window> m_Window;
	Sptr<Yuzu::World> m_World;
	
};





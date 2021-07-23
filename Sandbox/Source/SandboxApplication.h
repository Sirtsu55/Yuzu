#pragma once
#include "Yuzu.h"

class SandboxApp : public Yuzu::Application
{
public:
	SandboxApp();
	~SandboxApp();

	void Run() override;
	void OnUpdate(float DeltaTime) override;


private:
	Sptr<Yuzu::Window> m_Window;
};





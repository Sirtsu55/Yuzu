#pragma once

#include "Yuzu.h"


namespace Yuzu
{
	void Initialize()
	{
		Yuzu::Log::Init();
		Yuzu::TimerWriter::StartSession("App");
		Yuzu::Renderer2D::InitializeDefaults();
	}

	void RunProgram(Application* App)
	{
		App->Init();
		App->Start();
		App->OnDestroy();
		
	}

	void RunGameLoop(const Sptr<Window>& Win)
	{
		Win->MainLoop();
	}
}



int main(int argc, char** argv)
{
	
	auto app = Yuzu::CreateApplication();
	Yuzu::RunProgram(app);
	delete app;
	
	return 0;
}
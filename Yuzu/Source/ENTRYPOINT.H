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
}



int main()
{

	auto app = Yuzu::CreateApplication();
	app->Run();
	app->OnDestroy();
	delete app;

}
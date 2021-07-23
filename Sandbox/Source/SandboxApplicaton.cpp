
#include "SandboxApplication.h"




Yuzu::Application* Yuzu::CreateApplication()
{
	return new SandboxApp();
}

SandboxApp::SandboxApp()
	:m_Window(new Yuzu::Window("sand", 1280, 720, 4, 5))
{

}
SandboxApp::~SandboxApp()
{
}

void SandboxApp::Run()
{
	m_Window.get()->SetApplication(this);
	m_Window->MainLoop();

}

void SandboxApp::OnUpdate(float DeltaTime)
{

	YZA_INFO("UPDATED");

}





int main()
{
	Yuzu::TimerWriter::StartSession("App");
	Yuzu::Log::Init();

	auto app = Yuzu::CreateApplication();
	app->Run();
	delete app;

}
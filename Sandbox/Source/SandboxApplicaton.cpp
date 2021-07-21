
#include "Yuzu.h"


class SandboxApp : public Yuzu::Application
{
public:
	SandboxApp();
	~SandboxApp();

	void Run() override;
	void OnUpdate(float DeltaTime);
private:
	Sptr<Yuzu::Window> m_Window;
};

Yuzu::Application* Yuzu::CreateApplication()
{
	return new SandboxApp();
}

SandboxApp::SandboxApp()
	:m_Window(new Yuzu::Window("sand", 1280, 720, 4, 5))
{
	//m_Window.get()->SetUpdateFunction(OnUpdate);

}
SandboxApp::~SandboxApp()
{

}

void SandboxApp::Run()
{
	//Testing Purposes
	m_Window->MainLoop();
	// Real Implementation Draft
	/*
	while (m_Window->WindowShouldClose())
	{
		m_Window.Update();
		this->OnUpdate();
		SandBoxHandleInputs();
	}
	*/
}

void SandboxApp::OnUpdate(float DeltaTime)
{
}





int main()
{
	Yuzu::Log::Init();


	auto app = Yuzu::CreateApplication();
	app->Run();
	delete app;

}
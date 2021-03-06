
#include "SandboxApplication.h"
#include "EntryPoint.h"

YZ_APPLICATION(SandboxApp);





void SandboxApp::Init()
{

	Yuzu::WindowInitSettings WindowSettings = { "SandBox", 1080, 1920, glm::vec4(0.32f, 0.12f, 0.25f, 1.0f), glm::vec2(16, 9) };
	ApplicationWindow = CreateSptr<Yuzu::Window>(WindowSettings);
	ApplicationWindow->SetApplication(this);

	Yuzu::WorldInitSettings Wset = { 0 };
	Wset.MaxLights = 100;

	m_World = CreateSptr<Yuzu::World>(Wset);
	Yuzu::World::SetAsCurrent(m_World);
	Yuzu::Initialize();
}

void SandboxApp::Start()
{

	MyEntity Square = MyEntity(m_World.get());


	Yuzu::RunGameLoop(ApplicationWindow);
}


void SandboxApp::OnUpdate(float DeltaTime)
{


	Yuzu::_FuncTimerCore::UpdateTimers();
	m_World->OnUpdate(DeltaTime);
}





void SandboxApp::OnWidgetRender(float Deltatime)
{

	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMouseInputs;

		glm::vec3 CamLoc = Yuzu::CameraHandler::GetCameraLocation();
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));


		ImGui::Begin(" ", 0, window_flags);
		ImGui::Text("Camera");
		ImGui::Text("X: %f	Y: %f	Z: %f", CamLoc.x, CamLoc.y, CamLoc.z);
		ImGui::Separator();
		ImGui::Text("Time Elapsed: %f", Yuzu::GetElapsedSeconds());

		ImGui::Separator();
		ImGui::Text("FrameRate: %f", 1/Deltatime);
		ImGui::Text("FrameTime: %fms", Deltatime * 1000);
		ImGui::Endd();
	}




}

void SandboxApp::OnDestroy()
{
	
	//delete m_BRenderer;
}
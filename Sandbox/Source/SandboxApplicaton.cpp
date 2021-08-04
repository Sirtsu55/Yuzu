
#include "SandboxApplication.h"
#include "EntryPoint.h"

Yuzu::Application* Yuzu::CreateApplication()
{
	return new SandboxApp();
}

SandboxApp::SandboxApp()
	: m_World(CreateSptr<Yuzu::World>())
{
	Yuzu::WindowInitSettings WindowSettings = { "SandBox", 720, 1024, glm::vec4(0.32f, 0.12f, 0.25f, 1.0f), glm::vec2(16, 9) };
	
	m_Window = CreateSptr<Yuzu::Window>(WindowSettings);
	m_Window->SetApplication(this);
	Yuzu::World::SetAsCurrent(m_World);
	Yuzu::Initialize();
}


SandboxApp::~SandboxApp()
{
}

void SandboxApp::Run()
{

	auto Square = MyEntity(m_World.get(), Yuzu::PrimitiveShape::Square);
	//m_Square = MyEntity(m_World.get(), Yuzu::PrimitiveShape::Square);
	Yuzu::BatchSettings BSettings = { 120, 180 , "Resources/Shaders/TexturedSquare.glsl"};
	m_BRenderer = new Yuzu::BatchRenderer2D(BSettings);

	Yuzu::Vertex VertDestination[20];
	unsigned int IdxDestination[32];
	unsigned int layout[6] = { 0, 1, 2, 1, 2, 3 };


	Yuzu::QuadSettings VertSettings;
	VertSettings.Color = m_ChunkColor;
	VertSettings.Position = glm::vec3(1.0f);
	VertSettings.Size = 2.0f;
	VertSettings.TexID = 2.0f;
	for (int i = 0; i < 5; i++)
	{

		Yuzu::BatchRenderer2D::CreateQuads(&VertDestination[(4 * i)], VertSettings);
	}
	for (int i = 0; i < 5; i++)
	{
		m_BRenderer->CreateIndices(&IdxDestination[0] + (6 * i), &layout[0], 6, 3);
	}

	
	m_ChunkID = m_BRenderer->InsertVertices(&VertDestination[0], 20, &IdxDestination[0], 30);
	m_BRenderer->Flush();
	
	
	
	m_Window->MainLoop();
}



void SandboxApp::OnUpdate(float DeltaTime)
{

	{
		YZ_PROFILE_FUNCTION();
		m_BRenderer->ChangeColor(m_ChunkID, m_ChunkColor);
		m_BRenderer->Flush();
		m_BRenderer->RenderBatch();
	}
	m_World->OnUpdate(DeltaTime);
}





void SandboxApp::OnWidgetRender(float Deltatime)
{

	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMouseInputs;

		glm::vec3 CamLoc = Yuzu::Camera::GetCurrentCamera()->GetLocation();
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));


		ImGui::Begin(" ", 0, window_flags);
		ImGui::Text("Camera", CamLoc.x, CamLoc.y, CamLoc.z);
		ImGui::Text("X: %f	Y: %f	Z: %f", CamLoc.x, CamLoc.y, CamLoc.z);
		ImGui::End();
	}


	{
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

		glm::vec3 CamLoc = Yuzu::Camera::GetCurrentCamera()->GetLocation();

		
		ImGui::Begin("ChunkColor", 0, window_flags);
		ImGui::SliderFloat4("Color", glm::value_ptr(m_ChunkColor),0.0f, 1.0f);
		ImGui::End();
	}

}

void SandboxApp::OnDestroy()
{
	
	delete m_BRenderer;
}
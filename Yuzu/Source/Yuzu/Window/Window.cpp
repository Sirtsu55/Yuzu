#include "Core.h"

#include "Window.h"
#include "Rendering/Objects/Shader.h"
#include "Timer/Timer.h"
#include "Rendering/Objects/VertexArray.h"
#include "Rendering/Objects/VertexBuffer.h"
#include "Rendering/Objects/VertexBufferLayout.h"
#include "Rendering/Objects/ElementBuffer.h"
#include "Rendering/Objects/Texture.h"
#include "Rendering/Renderer/Renderer.h"
#include "Rendering/Renderer/BatchRenderer.h"


#include "World/Camera.h"


namespace Yuzu
{
	int Window::Width;
	int Window::Height;
	float Window::FrameTime;
	float Window::AspectRatio = 16 / 9;




	static bool firstMouse = false;

	static void framebufferesize(GLFWwindow* window, int width, int height)
	{

		Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

		if (handler)
		{
			handler->SetResolution(width, height);
		}
	}
	static void scrollcallback(GLFWwindow* window, double xoffset, double yoffset)
	{

		Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));

		if (handler)
		{
			handler->HandleScroll(yoffset);
		}
	}



	Window::Window(const std::string& name, int width, int height, int MajorVersion, int MinorVersion)
		: m_name(name)
	{
		Width = width;
		Height = height;
		if (!glfwInit())
		{
			YZC_CRITICAL("GLFW not initialized");
			throw "GLFW Failed to initialize";
		}

		const char* glsl_version = "#version 450";

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MajorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MinorVersion);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		

		m_window = glfwCreateWindow(Width, Height, m_name.c_str(), NULL, NULL);

		glfwSetWindowAspectRatio(m_window, 16, 9);


		glfwMakeContextCurrent(m_window);

		if (!gladLoadGL())
		{
			YZC_CRITICAL("GLAD not initialized");
			glfwSetWindowShouldClose(m_window, true);
		}
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(m_window, true);
		ImGui_ImplOpenGL3_Init("#version 450");

		ImGui::StyleColorsDark();
		glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));

		glfwSetFramebufferSizeCallback(m_window, framebufferesize);
		glfwSetScrollCallback(m_window, scrollcallback);

#if DEBUG_LEVEL > 0
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLErrorCallback, NULL);
#endif // DEBUG_LEVEL
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	}

	Window::~Window()
	{
	}

	//float* vertices = new float[]
	//{

	//	-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//	-1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	//	 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	//	-2.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.25f, 1.0f,
	//	-2.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.25f, 1.0f,
	//	-1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.25f, 1.0f,
	//	-1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.25f, 1.0f,
	//};

	unsigned char indices[] = { 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7 };

	void Window::MainLoop()
	{
		Yuzu::Camera cam(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, 5.0f);

		cam.Activate();

		//Yuzu::VertexArray vao;


		//vao.Bind();
		//Yuzu::Shader shader("Source/Shaders/TexturedSquare.glsl");


		//Yuzu::VertexBuffer vb(NULL, sizeof(Vertex) * 500, GL_DYNAMIC_DRAW);

		//vb.Bind();


		//Yuzu::VertexBufferLayout layout;
		//layout.Push<float>(3);
		//layout.Push<float>(4);
		//layout.Push<float>(2);
		//layout.Push<float>(1);


		//vao.AddBuffer(vb, layout);
		//Yuzu::ElementBuffer ebo(indices, 12, GL_STATIC_DRAW, GL_UNSIGNED_BYTE);


		//glm::mat4 ModelMat(1.0f), ViewProjMat(1.0f);
		//ViewProjMat = Yuzu::Camera::GetCurrentCamera()->GetViewProjectionMatrix();
		//glm::mat4 MVP = ViewProjMat * ModelMat;

		//shader.Bind();

		//shader.SetMat4("MVPMatrix", MVP);

		//Sptr<Yuzu::Texture> tex1 = std::make_shared<Yuzu::Texture>("Resources/smiley.png");

		//shader.SetInt("Image1", 0);

		//shader.InsertTexture(tex1.get(), 0);


		Yuzu::Renderer renderer;

		BatchSettings Settings;
		Settings.MaxIndices = 1000;
		Settings.MaxQuads = 2000;
		Settings.m_ShaderPath = "Source/Shaders/TexturedSquare.glsl";

		BatchRenderer::Init(Settings);
		Sptr<Texture> Tex1 = std::make_shared<Texture>("Resources/smiley.png");

		BatchRenderer::InsertTexture(Tex1, 0);

		for (unsigned int j = 0; j < 10; j++)
		{
			Vertex* MyQuads = new Vertex[100];

			for (unsigned int i = 0; i < 100; i += 4)
			{
				QuadSettings quad_s = { glm::vec3((i / 2),(float)j * 2, 1.0f), 0.0f, 1.0f };
				BatchRenderer::CreateQuads(MyQuads + i, quad_s);
			}
			BatchRenderer::InsertQuad(MyQuads, 20);
			delete[] MyQuads;
		}
		glm::vec3 QuadPos(0.0f);



		Yuzu::Timer FrameTimer;



		while (!glfwWindowShouldClose(m_window))
		{
			FrameTimer.Start();
			StartFrame();
			renderer.Clear();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		

			BatchRenderer::RenderBatch();

			{
				ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMouseInputs;

				glm::vec3 CamLoc = Camera::GetCurrentCamera()->GetLocation();
				ImGui::SetNextWindowBgAlpha(0.0f);
				ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));


				ImGui::Begin(" ", 0, window_flags);
				ImGui::Text("Camera", CamLoc.x, CamLoc.y, CamLoc.z);
				ImGui::Text("X: %f	Y: %f	Z: %f", CamLoc.x, CamLoc.y, CamLoc.z);
				ImGui::End();

			}
			{

				ImGui::Begin("QuadPos");
				ImGui::DragFloat3("Pos", glm::value_ptr(QuadPos), 0.005f);
				ImGui::End();
			}

			ImGui::Render();



			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			SwapBuffers();
			HandleInput();

			FrameTime = static_cast<float>(FrameTimer.End(Timer::Accuracy::Seconds));
		}
		BatchRenderer::ShutDown();
	}





	void Window::StartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_window);

	}

	void Window::HandleInput()
	{
		glfwPollEvents();

		if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_window, true);
		}

		if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Yuzu::Camera::GetCurrentCamera()->Move(Yuzu::Camera::Movement::Up, FrameTime);
			YZC_TRACE("W Pressed");


		}
		if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Yuzu::Camera::GetCurrentCamera()->Move(Yuzu::Camera::Movement::Down, FrameTime);
			YZC_TRACE("S Pressed");

		}

		if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Yuzu::Camera::GetCurrentCamera()->Move(Yuzu::Camera::Movement::Left, FrameTime);
			YZC_TRACE("A Pressed");


		}
		if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Yuzu::Camera::GetCurrentCamera()->Move(Yuzu::Camera::Movement::Right, FrameTime);
			YZC_TRACE("D Pressed");

		}
		HandleMouse();
	}

	void Window::HandleMouse()
	{
		double xPos, yPos;
		glfwGetCursorPos(m_window, &xPos, &yPos);

	}

	void Window::HandleScroll(double yoffset)
	{
		YZC_TRACE("Scrolled");

		if (yoffset > 0.0)
		{
			Yuzu::Camera::GetCurrentCamera()->Move(Yuzu::Camera::Movement::Forward, FrameTime);
		}
		else if (yoffset < 0.0)
		{
			Yuzu::Camera::GetCurrentCamera()->Move(Yuzu::Camera::Movement::Back, FrameTime);
		}
	}
	void Window::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(m_window);
		glfwTerminate();

	}

	void Window::SetResolution(int x, int y)
	{
		Width = x;
		Height = y;
		glViewport(0, 0, x, y);
	}


}
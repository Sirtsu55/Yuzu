#include "Core.h"

#include "InputListener.h"
#include "Window.h"
#include "Rendering/Renderer/Renderer.h"
#include "World/World.h"
#include "Rendering/Objects/Shader.h"


namespace Yuzu
{
	int Window::Width;
	int Window::Height;
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
	

	Window::Window(const WindowInitSettings& Settings)
		: m_Settings(Settings)
	{
		Width = Settings.WindowWidth;
		Height = Settings.WindowHeight;
		if (!glfwInit())
		{
			YZC_CRITICAL("GLFW not initialized");
			throw "GLFW Failed to initialize";
		}

	

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		

		m_window = glfwCreateWindow(Width, Height, Settings.WindowName.c_str() , NULL, NULL);


		
		glfwSetWindowAspectRatio(m_window, (int)m_Settings.AspectRatio.x, (int)m_Settings.AspectRatio.y);

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

		glfwSwapInterval(0);
#if DEBUG_LEVEL > 0
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLErrorCallback, NULL);
#endif // DEBUG_LEVEL
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		InputListener::SetListeningWindow(m_window, Settings.MinNumberOfKeyBinds);
		

	}

	Window::~Window()
	{
	}
	

	void Window::MainLoop()
	{

		Yuzu::SimpleTimer FrameTimer;

		
		
		

		while (!glfwWindowShouldClose(m_window))
		{
			YZ_PROFILE_NO_LOG("FrameTime");
			FrameTimer.Start();


			ImguiStartFrame();
			Renderer2D::Clear();
			glClearColor(m_Settings.BackgroundColor.x , m_Settings.BackgroundColor.y, m_Settings.BackgroundColor.z, m_Settings.BackgroundColor.w);


			glfwPollEvents();
			m_App->OnUpdate(Yuzu::World::FrameTimeStep.Seconds);
			RenderWindow();
			m_App->OnWidgetRender(Yuzu::World::FrameTimeStep.Seconds);


			RenderImgui();
			SwapBuffers();
			

			World::FrameTimeStep.Seconds = FrameTimer.Endf(Yuzu::TimerAccuracy::Seconds);
			World::FrameTimeStep.Milliseconds = FrameTimer.Endf(Yuzu::TimerAccuracy::MilliSec);
			World::FrameTimeStep.MicroSeconds = FrameTimer.Endf(Yuzu::TimerAccuracy::MicroSec);
		}
	
	}

	void Window::RenderWindow() const
	{
		World::RenderWorld();

	}




	void Window::ImguiStartFrame() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(m_window);

	}

	


	inline void Window::RenderImgui()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void Window::Terminate()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(m_window);
		glfwTerminate();

	}

	void Window::SetApplication(Application* App)
	{
		m_App = App;

	}


	void Window::SetResolution(int x, int y)
	{
		Width = x;
		Height = y;
		glViewport(0, 0, x, y);
	}


}
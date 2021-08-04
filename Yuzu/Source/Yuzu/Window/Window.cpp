#include "Core.h"

#include "InputListener.h"
#include "Window.h"
#include "Rendering/Objects/Shader.h"
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
	float Window::FrameTime = 0.0f;
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
		glfwSetScrollCallback(m_window, scrollcallback);

#if DEBUG_LEVEL > 0
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(OpenGLErrorCallback, NULL);
#endif // DEBUG_LEVEL
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		InputListener::SetListeningWindow(m_window);
		

	}

	Window::~Window()
	{
	}



	unsigned int* indices = new unsigned int[12] { 0, 1, 2, 1, 2, 3, 4, 5, 6, 5, 6, 7 };

	void Window::MainLoop()
	{

		Yuzu::SimpleTimer FrameTimer;
		Yuzu::Camera cam(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 5.0f, 5.0f);
		cam.Activate();

		while (!glfwWindowShouldClose(m_window))
		{
			YZ_PROFILE("FrameTime");



			FrameTimer.Start();
			ImguiStartFrame();
			Renderer2D::Clear();
			glClearColor(m_Settings.BackgroundColor.x , m_Settings.BackgroundColor.y, m_Settings.BackgroundColor.z, m_Settings.BackgroundColor.w);


			m_App->OnUpdate(FrameTime);


			m_App->OnWidgetRender(FrameTime);


			RenderImgui();
			SwapBuffers();
			HandleInput();


			FrameTime = static_cast<float>(FrameTimer.End(TimerAccuracy::Seconds));
		}
	
	}





	void Window::ImguiStartFrame()
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
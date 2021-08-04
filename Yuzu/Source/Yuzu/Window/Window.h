#pragma once

#include "GLFW/glfw3.h"
#include "Application.h"


namespace Yuzu
{

	struct WindowInitSettings
	{
		std::string WindowName;
		int WindowHeight;
		int WindowWidth;
		glm::vec4 BackgroundColor;

		glm::vec2 AspectRatio = { 16 , 9 };

	};

	class Window
	{
	public:
		Window(const WindowInitSettings& Settings);
		~Window();


		void MainLoop();
		void Terminate();
		void SetApplication(Application* App);

		void SetResolution(int x, int y);
		void HandleScroll(double yoffset);
		bool WindowShouldClose() { return glfwWindowShouldClose(m_window); }
		
		
		inline void RenderImgui();

		static int Width;
		static int Height;
		static float AspectRatio;
		static float FrameTime;

	private:

		GLFWwindow* m_window;
		Application* m_App;
		WindowInitSettings m_Settings;



		void ImguiStartFrame();
		void SwapBuffers();
		void HandleInput();
		void HandleMouse();



	};

}
#pragma once

#include "GLFW/glfw3.h"
#include "Application.h"


namespace Yuzu
{

	class Window
	{
	public:
		Window(const std::string& name, int width, int height, int MajorVersion, int MinorVersion);
		~Window();


		void MainLoop();
		void Terminate();
		void SetApplication(Application* App);

		void SetResolution(int x, int y);
		void HandleScroll(double yoffset);
		bool WindowShouldClose() { return glfwWindowShouldClose(m_window); }
		
		
		static int Width;
		static int Height;
		static float AspectRatio;

		static float FrameTime;

	private:

		GLFWwindow* m_window;
		std::string m_name;
		Application* m_App;



		void StartFrame();
		void SwapBuffers();
		void HandleInput();
		void HandleMouse();



	};

}
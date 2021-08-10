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

		int MinNumberOfKeyBinds = 20;

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
		bool WindowShouldClose() { return glfwWindowShouldClose(m_window); }
		
		
		inline void RenderImgui();

		static int Width;
		static int Height;
		static float AspectRatio;

	private:

		GLFWwindow* m_window;
		Application* m_App;
		WindowInitSettings m_Settings;



		void RenderWindow() const;
		void ImguiStartFrame() const;
		void SwapBuffers() const;



	};

}
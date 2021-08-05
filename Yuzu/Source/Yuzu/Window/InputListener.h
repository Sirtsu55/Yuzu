#pragma once
#include "InputKeys.h"
#include <unordered_map>
#include <GLFW/glfw3.h>


namespace Yuzu 
{

	class InputListener
	{

	public:

		static void AddListeningKey(InputKey key);
		static void AddListeningMouseKey(MouseButton key);
		static void SetListeningWindow(GLFWwindow* window);
		static void UpdateKeys();
		static std::unordered_map<InputKey, KeyState>& GetKeysPressed();
		static std::unordered_map<MouseButton, KeyState>& GetMouseButtonsPressed();
		static void UpdateKey(InputKey key, int Action);
		static void UpdateCursor(double* x, double* y);
		static void UpdateMouseButtons(double* x, double* y);
	private:
		static GLFWwindow* s_ListeningWindow;
		static std::unordered_map<InputKey, KeyState> s_KeyBinds;
		static std::unordered_map<MouseButton, KeyState> s_MouseBinds;
		static glm::dvec2 s_MousePos;

		InputListener() = delete;
	};

}





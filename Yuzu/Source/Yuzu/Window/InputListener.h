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
		static void SetListeningWindow(GLFWwindow* window, int MinNumOfInputs);
		static std::unordered_map<InputKey, KeyState>& GetKeysPressed();
		static void UpdateKey(InputKey key, KeyState Action);
		static void UpdateCursor(double* x, double* y);
	private:
		static GLFWwindow* s_ListeningWindow;
		static std::unordered_map<InputKey, KeyState> s_KeyBinds;
		static glm::dvec2 s_MousePos;

		InputListener() = delete;
	};

}





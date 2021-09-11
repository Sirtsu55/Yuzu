#pragma once
#include "InputKeys.h"
#include <unordered_map>
#include <GLFW/glfw3.h>

namespace Yuzu 
{
	struct InputComponent;

	class InputListener
	{

	public:

		static void SetListeningWindow(GLFWwindow* window, int MinNumOfInputs);
		static std::unordered_map<InputKey, KeyState>& GetKeysPressed();
		static KeyState GetKeyState(InputKey key);
		static void UpdateKey(InputKey key, KeyState Action);
		static void UpdateCursor(double* x, double* y);

		static void _SetInputComp(InputComponent* comp);
		static void _DelInputComp(InputComponent* comp);
	private:
		static GLFWwindow* s_ListeningWindow;
		static std::unordered_map<InputKey, KeyState> s_KeyBinds;
		static std::list<InputComponent*> s_InputComps;
		static glm::dvec2 s_MousePos;

		InputListener() = delete;
	};

}





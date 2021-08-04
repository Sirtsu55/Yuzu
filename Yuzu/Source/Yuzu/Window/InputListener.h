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
		static void SetListeningWindow(GLFWwindow* window);
		static void UpdateKeys();
		static std::unordered_map<InputKey, bool>& GetKeysPressed();
	
	private:
		static GLFWwindow* s_ListeningWindow;
		static std::unordered_map<InputKey, bool> s_KeyBinds;

	};

}





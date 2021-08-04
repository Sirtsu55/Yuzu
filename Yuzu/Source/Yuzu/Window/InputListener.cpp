#include "Core.h"
#include "InputListener.h"


namespace Yuzu
{

	GLFWwindow* InputListener::s_ListeningWindow;
	std::unordered_map<InputKey, bool> InputListener::s_KeyBinds;

	void InputListener::AddListeningKey(InputKey key)
	{
		s_KeyBinds[key] = false;
	}
	void InputListener::SetListeningWindow(GLFWwindow* window)
	{
		s_ListeningWindow = window;
	}

	void InputListener::UpdateKeys()
	{
		for (auto& [Key, IsPressed] : s_KeyBinds)
		{
			s_KeyBinds[Key] = glfwGetKey(s_ListeningWindow, (int)Key);

		}

	}

	std::unordered_map<InputKey, bool>& InputListener::GetKeysPressed()
	{
		return s_KeyBinds;
	}
	

}

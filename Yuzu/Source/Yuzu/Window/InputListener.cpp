#include "Core.h"
#include "InputListener.h"


static void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	Yuzu::InputListener::UpdateCursor(&xpos, &ypos);
}

namespace Yuzu
{

	GLFWwindow* InputListener::s_ListeningWindow;
	std::unordered_map<InputKey, KeyState> InputListener::s_KeyBinds;
	std::unordered_map<MouseButton, KeyState> InputListener::s_MouseBinds;
	glm::dvec2 InputListener::s_MousePos;

	void InputListener::AddListeningKey(InputKey key)
	{
		s_KeyBinds[key] = KeyState::Released;
	}
	void InputListener::AddListeningMouseKey(MouseButton key)
	{
		s_MouseBinds[key] = KeyState::Released;
	}
	void InputListener::SetListeningWindow(GLFWwindow* window)
	{
		s_KeyBinds.clear();
		s_MouseBinds.clear();
		s_ListeningWindow = window;
		glfwSetCursorPosCallback(s_ListeningWindow, cursor_callback);
	}

	void InputListener::UpdateKeys()
	{
		for (auto& [Key, IsPressed] : s_KeyBinds)
		{
			s_KeyBinds[Key] = (KeyState)glfwGetKey(s_ListeningWindow, (int)Key);

		}
		for (auto& [MouseKey, MouseIsPressed] : s_MouseBinds)
		{
			s_MouseBinds[MouseKey] = (KeyState)glfwGetMouseButton(s_ListeningWindow, (int)MouseKey);

		}

	}

	std::unordered_map<InputKey, KeyState>& InputListener::GetKeysPressed()
	{
		return s_KeyBinds;
	} 

	std::unordered_map<MouseButton, KeyState>& InputListener::GetMouseButtonsPressed()
	{
		return s_MouseBinds;
	}

	void InputListener::UpdateCursor(double* x, double* y)
	{
		s_MousePos.x = *x;
		s_MousePos.y = *y;

	}

}

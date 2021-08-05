#include "Core.h"
#include "InputListener.h"


static void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	Yuzu::InputListener::UpdateCursor(&xpos, &ypos);
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	Yuzu::InputListener::UpdateKey((Yuzu::InputKey)button, (Yuzu::KeyState)action);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Yuzu::InputListener::UpdateKey((Yuzu::InputKey)key, (Yuzu::KeyState)action);
}

namespace Yuzu
{

	GLFWwindow* InputListener::s_ListeningWindow;
	std::unordered_map<InputKey, KeyState> InputListener::s_KeyBinds;
	glm::dvec2 InputListener::s_MousePos;

	void InputListener::AddListeningKey(InputKey key)
	{
		s_KeyBinds[key] = KeyState::Released;
	}

	void InputListener::SetListeningWindow(GLFWwindow* window, int MinNumOfInputs)
	{
		s_KeyBinds.clear();
		s_KeyBinds.reserve(MinNumOfInputs);
		s_ListeningWindow = window;
		glfwSetKeyCallback(s_ListeningWindow, key_callback);
		glfwSetMouseButtonCallback(s_ListeningWindow, mouse_button_callback);
		glfwSetCursorPosCallback(s_ListeningWindow, cursor_callback);
	}


	std::unordered_map<InputKey, KeyState>& InputListener::GetKeysPressed()
	{
		return s_KeyBinds;
	} 


	void InputListener::UpdateKey(InputKey key, KeyState Action)
	{
		s_KeyBinds[key] = Action;
	}

	void InputListener::UpdateCursor(double* x, double* y)
	{
		s_MousePos.x = *x;
		s_MousePos.y = *y;

	}

}

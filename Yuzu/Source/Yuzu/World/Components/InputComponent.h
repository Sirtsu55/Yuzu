#pragma once
#include "Yuzu/Window/InputListener.h"
#include "Yuzu/World/Entities/Entity.h"

namespace Yuzu
{


	struct InputComponent
	{

		InputComponent() = default;
		InputComponent(Entity* Parent, int MinNumOfKeyBinds)
			: EntityObject(Parent), init(true)
		{
			Keybinds.reserve(MinNumOfKeyBinds);
			InputListener::_SetInputComp(this);
		}
		~InputComponent()
		{
			if (init)
			{
				InputListener::_DelInputComp(this); 
			}
		}
		InputComponent(const InputComponent&) = default;

		std::unordered_map<InputKey, void(Entity::*)(KeyState)> Keybinds;
		std::vector<InputKey> ContinuousUpdateKeys;
		
		void AddKeybind(InputKey KeyToAdd, void(Entity::*EventFunc)(KeyState))
		{
			if (EntityObject)
			{
				Keybinds[KeyToAdd] = EventFunc;

			}
		}

		void AddContinuousKeybind(InputKey KeyToAdd, void(Entity::* EventFunc)(KeyState))
		{
			if (EntityObject)
			{
				Keybinds[KeyToAdd] = EventFunc;
				ContinuousUpdateKeys.push_back(KeyToAdd);

			}
		}


		void Call(InputKey key, KeyState state)
		{
			auto KeyStatePair = Keybinds.find(key);
			if (KeyStatePair != Keybinds.end())
			{
				(EntityObject->*(KeyStatePair->second))(state);
			}
			
		}

		void UpdateContinuousKeys()
		{
			for (auto Key : ContinuousUpdateKeys)
			{
				(EntityObject->*(Keybinds[Key]))(InputListener::GetKeyState(Key));
			}
		}


		Entity* EntityObject = nullptr;

	private:
		bool init = false;
		
		
	};
}



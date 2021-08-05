#pragma once
#include "Yuzu/Window/InputListener.h"
#include "Yuzu/World/Entities/Entity.h"

namespace Yuzu
{


	struct InputComponent
	{

		InputComponent() = default;
		InputComponent(Entity * Parent)
			: EntityObject(Parent)
		{
		}

		~InputComponent() = default;
		InputComponent(const InputComponent&) = default;

		std::unordered_map<InputKey, void(Entity::*)(void)> Keybinds;
		std::unordered_map<MouseButton, void(Entity::*)(void)> MouseBinds;
		
		void AddKeybind(InputKey KeyToAdd, void(Entity::* EventFunc)(void))
		{
			if (EntityObject)
			{
				Keybinds[KeyToAdd] = EventFunc;
				InputListener::AddListeningKey(KeyToAdd);
			}
		}
		void AddMouseBind(MouseButton KeyToAdd, void(Entity::* EventFunc)(void))
		{
			if (EntityObject)
			{
				MouseBinds[KeyToAdd] = EventFunc;
				InputListener::AddListeningMouseKey(KeyToAdd);
			}
		}
		void BroadcastKeyInput(std::unordered_map<InputKey, KeyState>& Keys, std::unordered_map<MouseButton, KeyState>& MouseKeys)
		{
			if (EntityObject)
			{
				
				for( auto& [Key, KeyFunction] : Keybinds)
				{ 
					if (Keys[Key] == KeyState::Pressed)
					{
						(EntityObject->*(KeyFunction))();
					}
				}

				for (auto& [MouseKey, MouseFunction] : MouseBinds)
				{
					if (MouseKeys[MouseKey] == KeyState::Pressed)
					{
						(EntityObject->*(MouseFunction))();
					}
				}

			}

		}



		Entity* EntityObject = nullptr;
		
		
	};
}



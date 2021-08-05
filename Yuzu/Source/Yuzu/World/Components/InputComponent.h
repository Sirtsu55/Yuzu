#pragma once
#include "Yuzu/Window/InputListener.h"
#include "Yuzu/World/Entities/Entity.h"

namespace Yuzu
{


	struct InputComponent
	{

		InputComponent() = default;
		InputComponent(Entity* Parent, int MinNumOfKeyBinds)
			: EntityObject(Parent)
		{
			Keybinds.reserve(MinNumOfKeyBinds);
		}
		~InputComponent() = default;
		InputComponent(const InputComponent&) = default;

		std::unordered_map<InputKey, void(Entity::*)(void)> Keybinds;

		
		void AddKeybind(InputKey KeyToAdd, void(Entity::* EventFunc)(void))
		{
			if (EntityObject)
			{
				Keybinds[KeyToAdd] = EventFunc;
				InputListener::AddListeningKey(KeyToAdd);
			}
		}
	
		void BroadcastKeyInput(std::unordered_map<InputKey, KeyState>& Keys)
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



			}

		}



		Entity* EntityObject = nullptr;
		
		
	};
}



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
		
		void AddKeybind(InputKey KeyToAdd, void(Entity::* EventFunc)(void))
		{
			if (EntityObject)
			{
				Keybinds[KeyToAdd] = EventFunc;
				InputListener::AddListeningKey(KeyToAdd);
			}
		}

		void BroadcastKeyInput(std::unordered_map<InputKey, bool> Keys)
		{
			if (EntityObject)
			{
				for (auto& [Key, KeyState] : Keys)
				{
					if (KeyState == true)
					{
						
						(EntityObject->*(Keybinds[Key]))();
					}

				}
			}

		}

		Entity* EntityObject = nullptr;
		
		
	};
}



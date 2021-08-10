#pragma once
#include <string>
#include "Entity.h"
#include "Yuzu/World/Components/Components.h"
namespace Yuzu
{
	class TagEntity : public Entity
	{
	public:
		TagEntity(Yuzu::World* world, const std::string& name)
			: Entity(world)
		{
			AddComponent<Yuzu::TagComponent>(name);
		}
		TagEntity() = default;
		~TagEntity() = default;

	private:
		

	};




}

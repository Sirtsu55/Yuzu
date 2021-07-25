#include "Core.h"
#include "World.h"
#include "Core.h"

#include"World.h"
namespace Yuzu
{
    World::~World()
    {
        delete WorldInstance;
    }
    World* Yuzu::World::GetWorld()
    {
        if (WorldInstance)
        {
            return WorldInstance;
        }
        else
        {
            WorldInstance = new World();
            return WorldInstance;
        }
    }
}
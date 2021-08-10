#include "Core.h"
#include "World.h"
#include "Components/Components.h"
#include "Rendering/Renderer/Renderer.h"
namespace Yuzu
{
    World* World::m_CurrentWorld = nullptr;
    TimeStep World::FrameTimeStep;
    


    World::World()
    {
    }

    World::~World()
    {
    }


    void World::RenderWorld()
    {
        
        auto RenderingGroup = GetWorld()->m_Registry.group<TransformComponent, TexturedSpriteComponent>();
        for (auto RenderingEntity : RenderingGroup)
        {
            auto [Transform, Sprite] = RenderingGroup.get<TransformComponent, TexturedSpriteComponent>(RenderingEntity);

            Renderer2D::DrawSprite(Transform, Sprite);

        }

    }
    
    void World::OnUpdate(float DeltaTime)
    {


        auto TickView = m_Registry.view<TickComponent>();
        TickView.each([&DeltaTime](TickComponent& TickCmp)
            {
                TickCmp.Update(DeltaTime);
            });


        
        auto& KeyInp = InputListener::GetKeysPressed();

        auto InputView = m_Registry.view<InputComponent>();
        InputView.each([&KeyInp](InputComponent& InputCmp)
            {
                InputCmp.BroadcastKeyInput(KeyInp);
            });
    }
        

          
}
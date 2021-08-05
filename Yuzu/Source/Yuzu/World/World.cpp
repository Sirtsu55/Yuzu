#include "Core.h"
#include "World.h"
#include "Components/Components.h"
#include "Rendering/Renderer/Renderer.h"
namespace Yuzu
{
    World* World::m_CurrentWorld = nullptr;

    


    World::World()
    {
        
    }

    World::~World()
    {
    }
    
    
    void World::OnUpdate(float DeltaTime)
    {
        auto RenderingGroup = m_Registry.group<TransformComponent, TexturedSpriteComponent>();
        for (auto RenderingEntity : RenderingGroup)
        {
            auto [Transform, Sprite] = RenderingGroup.get<TransformComponent, TexturedSpriteComponent>(RenderingEntity);

            Renderer2D::DrawSprite(Transform, Sprite);

        }

        auto TickView = m_Registry.view<TickComponent>();
        TickView.each([&DeltaTime](TickComponent& TickCmp)
            {
                TickCmp.Update(DeltaTime);
            });


        InputListener::UpdateKeys();
        auto& KeyInp = InputListener::GetKeysPressed();
        auto& MouseInp = InputListener::GetMouseButtonsPressed();

        auto InputView = m_Registry.view<InputComponent>();
        InputView.each([&KeyInp, &MouseInp](InputComponent& InputCmp)
            {
                InputCmp.BroadcastKeyInput(KeyInp, MouseInp);
            });
    }
        

          
}
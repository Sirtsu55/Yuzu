#include "Core.h"
#include "World.h"
#include "Components/Components.h"
#include "Rendering/Renderer/Renderer.h"
#include "Rendering/Renderer/Lighter.h"
namespace Yuzu
{
    World* World::m_CurrentWorld = nullptr;
    TimeStep World::FrameTimeStep;
    
    

    World::World(const WorldInitSettings& Settings)
    {
        Lighter::_Init(Settings.MaxLights);
    }

    World::~World()
    {
    }


    void World::RenderWorld()
    {
        
        {
            auto TSRenderingGroup = GetWorld()->m_Registry.group<TransformComponent, SpriteComponent>();
           
            for (auto [RenderingEntity, Trans, Sprite] : TSRenderingGroup.each())
            {
                
                Renderer2D::DrawSprite(Trans, Sprite);

            }

        }


        
    }
    
    void World::OnUpdate(float DeltaTime)
    {


        auto TickView = m_Registry.view<TickComponent>();
        TickView.each([&DeltaTime](TickComponent& TickCmp)
            {
                TickCmp.Update(DeltaTime);
            });


        CameraHandler::Update();

    }
        

          
}
#include "ecsLifespan.h"
#include "ecsMesh.h"
#include "ecsPhys.h"
#include "RenderEngine.h"
#include "RenderThread.h"
#include "ecsSystems.h"

void register_ecs_lifespan_systems(flecs::world& ecs)
{
  ecs.system<Lifespan>()
    .each([&](flecs::entity ent, Lifespan &life)
    {
      life.lifetime += ent.delta_time();
    });

  static auto renderQuery = ecs.query<RenderEnginePtr>();
  ecs.system<Lifespan, RenderProxyPtr>()
    .each([&](flecs::entity ent, Lifespan& life, RenderProxyPtr &renderProxyPtr)
    {
      renderQuery.each([&](RenderEnginePtr re)
      {
        if (life.lifetime >= life.lifespan) {
          re.ptr->GetRT()->EnqueueCommand(RC_RemoveRenderObject, renderProxyPtr.ptr);
          ent.remove<RenderProxyPtr>();
        }
      });
    });

  ecs.system<Lifespan>()
    .each([&](flecs::entity ent, Lifespan& life)
    {
      if (life.lifetime > life.lifespan) {
        ent.destruct();
      }
    });
    
}

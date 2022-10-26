#include "EntitySystem.h"
#include "ecsSystems.h"
#include "ecsMesh.h"
#include "ecsControl.h"
#include "ecsPhys.h"

#include "../XmlParser.h"

EntitySystem::EntitySystem(RenderEngine* renderEngine, InputHandler* inputHandler, const char* EntityFilePath)
{
    ecs.entity("inputHandler")
        .set(InputHandlerPtr{ inputHandler });
    ecs.entity("renderEngine")
        .set(RenderEnginePtr{ renderEngine });

    XmlParser parser;
    parser.ParseDocument(EntityFilePath, ecs);

    register_ecs_mesh_systems(ecs);
    register_ecs_control_systems(ecs);
    register_ecs_phys_systems(ecs);
}

void EntitySystem::Update()
{
    ecs.progress();
}
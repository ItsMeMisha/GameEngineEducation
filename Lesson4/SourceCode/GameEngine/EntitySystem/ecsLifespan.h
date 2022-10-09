#pragma once
#include "flecs.h"

struct Lifespan 
{ 
  float lifespan;
  float lifetime;
};

void register_ecs_lifespan_systems(flecs::world& ecs);
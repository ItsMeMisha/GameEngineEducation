#pragma once
#include "flecs.h"

struct Controllable {};
struct JumpSpeed { float val; };

struct Shooter 
{
  bool lastKeyState = false;
  float shootCooldown = 0.5f;
  float shootDelayLeft = 0.f;
  float reloadCooldown = 5.f;
  float reloadDelayLeft = 0.f;
  int baseAmmo = 6;
  int currentAmmo = 6;
};

void register_ecs_control_systems(flecs::world &ecs);


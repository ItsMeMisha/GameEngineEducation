#include "ecsControl.h"
#include "ecsSystems.h"
#include "ecsPhys.h"
#include "ecsMesh.h"
#include "ecsLifespan.h"
#include "flecs.h"
#include "../InputHandler.h"

void register_ecs_control_systems(flecs::world &ecs)
{
  static auto inputQuery = ecs.query<InputHandlerPtr>();
  ecs.system<Velocity, const Speed, const Controllable>()
    .each([&](flecs::entity e, Velocity &vel, const Speed &spd, const Controllable &)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        float deltaVel = 0.f;
        if (input.ptr->GetInputState().test(eIC_GoLeft))
          deltaVel -= spd;
        if (input.ptr->GetInputState().test(eIC_GoRight))
          deltaVel += spd;
        vel.x += deltaVel * e.delta_time();
      });
    });

  ecs.system<const Position, Velocity, const Controllable, const BouncePlane, const JumpSpeed>()
    .each([&](const Position &pos, Velocity &vel, const Controllable &, const BouncePlane &plane, const JumpSpeed &jump)
    {
      inputQuery.each([&](InputHandlerPtr input)
      {
        constexpr float planeEpsilon = 0.1f;
        if (plane.x*pos.x + plane.y*pos.y + plane.z*pos.z < plane.w + planeEpsilon)
          if (input.ptr->GetInputState().test(eIC_Jump)) {
            vel.y = jump.val;
          }
      });
    });

  ecs.system<const Position, const Controllable, const BouncePlane, Shooter>()
    .each([&](flecs::entity ent, const Position &pos, const Controllable &, const BouncePlane &plane, Shooter &shooter)
    {
        inputQuery.each([&](InputHandlerPtr input)
        {
          bool newKeyState = input.ptr->GetInputState().test(eIC_Shoot);
          if (shooter.shootDelayLeft <= 0.1f) {
            if (newKeyState != shooter.lastKeyState && !shooter.lastKeyState) {
              ent.world().entity()
                .set(Position{ pos.x + 2.f, pos.y, pos.z })
                .set(Velocity{ 10.f, 7.f, 0.f })
                .set(Gravity{ 0.f, -9.8065f, 0.f })
                .set(plane)
                .set(Bounciness{ 0.f })
                .set(Lifespan{ 1.f, 0.f })
                .add<CubeMesh>();

              shooter.shootDelayLeft = shooter.shootCooldown;
            }
          }
          else {
            shooter.shootDelayLeft -= ent.delta_time();
          }
          shooter.lastKeyState = newKeyState;
        });
    });
}


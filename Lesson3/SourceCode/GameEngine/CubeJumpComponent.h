#pragma once

#include "ObjectComponent.h"

class CubeJumpComponent final : public ObjectComponent
{
public:
  CubeJumpComponent(GameObject* owner);
  void Update(float elapsedTime) override;

private:
  float m_TotalTime = 0.f;
  const float g = -9.8f;
  float m_InitialSpeed = 10.f;
  float m_LowerHeightLimit = 0.f;
};

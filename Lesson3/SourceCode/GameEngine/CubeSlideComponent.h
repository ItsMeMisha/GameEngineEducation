#pragma once

#include "ObjectComponent.h"

class CubeSlideComponent final : public ObjectComponent
{
  using ObjectComponent::ObjectComponent;
public:
  void Update(float elapsedTime) override;
private:
  float m_Speed = 2.f;
  float m_TotalTime = 0.f;
};
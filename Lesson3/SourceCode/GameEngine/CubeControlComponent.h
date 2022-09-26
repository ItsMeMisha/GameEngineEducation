#pragma once

#include "ObjectComponent.h"
#include "InputHandler.h"

class CubeControlComponent final : public ObjectComponent
{
public:
  CubeControlComponent(GameObject* owner, InputHandler* inputHandlerInstancePointer);

  void Update(float elapsedTime) override;
private:
  InputHandler* m_pInputHandler;

  float m_Speed = 4.f;
};

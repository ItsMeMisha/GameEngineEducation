#include "CubeControlComponent.h"

CubeControlComponent::CubeControlComponent(GameObject* owner, InputHandler* inputHandlerInstancePointer) : ObjectComponent(owner), m_pInputHandler(inputHandlerInstancePointer)
{
}

void CubeControlComponent::Update(float elapsedTime)
{
  if (m_pInputHandler == nullptr || m_pOwnerObject == nullptr) {
    return;
  }

  float modifier = 0.0f;
  if (m_pInputHandler->GetInputState().test(eIC_GoLeft))
    modifier -= 1.0f;
  if (m_pInputHandler->GetInputState().test(eIC_GoRight))
    modifier += 1.0f;

  float CurrentPosition[3] = {};
  m_pOwnerObject->GetPosition(CurrentPosition);
  CurrentPosition[0] += modifier * m_Speed * elapsedTime;
  m_pOwnerObject->SetPosition(CurrentPosition[0], CurrentPosition[1], CurrentPosition[2]);
}

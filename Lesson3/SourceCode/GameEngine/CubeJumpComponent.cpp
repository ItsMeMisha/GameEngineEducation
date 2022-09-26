#include "CubeJumpComponent.h"

CubeJumpComponent::CubeJumpComponent(GameObject* owner) : ObjectComponent(owner)
{
  if (owner != nullptr) {
    float CurrentPosition[3] = {};
    owner->GetPosition(CurrentPosition);
    m_LowerHeightLimit = CurrentPosition[1];
  }
}

void CubeJumpComponent::Update(float elapsedTime)
{
  if (m_pOwnerObject == nullptr) {
    return;
  }

  float CurrentPosition[3] = {};
  m_pOwnerObject->GetPosition(CurrentPosition);

  if (CurrentPosition[1] <= m_LowerHeightLimit) {
    m_TotalTime = 0.f;
  }
  m_TotalTime += elapsedTime;

  CurrentPosition[1] = m_InitialSpeed * m_TotalTime + g / 2 * m_TotalTime * m_TotalTime + m_LowerHeightLimit;
  m_pOwnerObject->SetPosition(CurrentPosition[0], CurrentPosition[1], CurrentPosition[2]);
}

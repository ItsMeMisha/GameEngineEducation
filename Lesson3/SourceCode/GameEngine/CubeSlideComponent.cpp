#include "CubeSlideComponent.h"
#include <cmath>

void CubeSlideComponent::Update(float elapsedTime)
{
  if (m_pOwnerObject == nullptr) {
    return;
  }

  float CurrentPosition[3] = {};
  m_pOwnerObject->GetPosition(CurrentPosition);
  CurrentPosition[2] -= m_Speed * sin(m_TotalTime);
  m_TotalTime += elapsedTime;
  CurrentPosition[2] += m_Speed * sin(m_TotalTime);
  m_pOwnerObject->SetPosition(CurrentPosition[0], CurrentPosition[1], CurrentPosition[2]);
}

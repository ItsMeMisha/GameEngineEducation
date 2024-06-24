#pragma once

#include "GameObject.h"

class ObjectComponent
{
public:
  ObjectComponent(GameObject* owner) : m_pOwnerObject(owner) {};

  virtual void Update(float elapsedTime) {};
  GameObject* GetOwner() { return m_pOwnerObject; }
protected:
  GameObject* m_pOwnerObject;
};
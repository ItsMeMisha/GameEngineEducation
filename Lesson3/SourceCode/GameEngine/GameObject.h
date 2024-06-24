#pragma once

#include "Common.h"
#include "RenderProxy.h"

class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
		if (m_pComponent != nullptr) {
			delete m_pComponent; //actually should delete component from outside or create it inside object 
		}
	}

	void SetPosition(float x, float y, float z);
	void GetPosition(float* result)
	{
		result[0] = m_vPosition[0];
		result[1] = m_vPosition[1];
		result[2] = m_vPosition[2];
	}

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }

	void SetComponent(class ObjectComponent* newComponent) { m_pComponent = newComponent; }
	class ObjectComponent* GetComponent() { return m_pComponent; }
protected:
	RenderProxy* m_pRenderProxy;

	float m_vPosition[3];

	class ObjectComponent* m_pComponent;
};


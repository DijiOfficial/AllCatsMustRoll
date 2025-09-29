#pragma once
#include "Engine/Components/Component.h"

namespace thomasWasLate
{
	class RotatingPlatform final  : public diji::Component
	{
	public:
		
		
		explicit RotatingPlatform(diji::GameObject* owner, float rotationSpeed = 50.f); // constructor with default rotation speed
		~RotatingPlatform() noexcept override = default; // override destructor
		
		
		void Update() override; //


	private:
		float m_RotationSpeed; // rotation speed in degrees per/sec
		float m_CurrentAngle = 0.f; // current angle of rotation
	};
}
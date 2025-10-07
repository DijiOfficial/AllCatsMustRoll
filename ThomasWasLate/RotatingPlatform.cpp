#include "RotatingPlatform.h"  
#include "Engine/Components/TextureComp.h"
#include <SFML/Window/Keyboard.hpp>  
#include "Engine/Core/GameObject.h"  
#include "Engine/Components/Transform.h"  
#include "Engine/Collision/Collider.h"  
#include "Engine/Singleton/TimeSingleton.h"  

using namespace thomasWasLate;  

// Constructor with rotation speed parameter
RotatingPlatform::RotatingPlatform(diji::GameObject* owner, float rotationSpeed)  
   : Component(owner), m_RotationSpeed(rotationSpeed)  
{  
}  

void RotatingPlatform::Init()  
{  

   m_Transform = GetOwner()->GetComponent<diji::Transform>();  
   m_Collider = GetOwner()->GetComponent<diji::Collider>();  
   m_TextureComp = GetOwner()->GetComponent<diji::TextureComp>(); // m_TextureComp is initialized  

   //collider  no gravity - no bounce  
   if (m_Collider)  
   {  
	   m_Collider->SetStatic(true);  // static platform
	   m_Collider->SetAffectedByGravity(false);  // no gravity
	   m_Collider->SetRestitution(0.f);   // no bounce
	   m_Collider->SetFriction(1.f);  // high friction - prevent slipping
   }  
   
   // Set origin to center for proper rotation
   if (m_TextureComp) {  
       m_TextureComp->SetOrigin({ (150.f/2), (45.f / 2) });//platform size/2 to get origin
   }  
}  

void RotatingPlatform::Update()  
{  
   if (!m_Transform) return;  

   const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime(); // Get delta time from TimeSingleton
   float rotation = m_Transform->GetRotation();  // Current rotation angle

   // Rotate with S and W
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))  
       rotation -= m_RotationSpeed * dt;  
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))  
       rotation += m_RotationSpeed * dt;  

   // Keep rotation within 0-360 degrees
   m_Transform->SetRotation(rotation);  

   if (m_TextureComp) {  
	   m_TextureComp->SetRotationAngle(rotation);// Update texture rotation
   }  
}

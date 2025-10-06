#include "RotatingPlatform.h"  
#include "Engine/Components/TextureComp.h" // Add this include to resolve the incomplete type issue  
#include <SFML/Window/Keyboard.hpp>  
#include "Engine/Core/GameObject.h"  
#include "Engine/Components/Transform.h"  
#include "Engine/Collision/Collider.h"  
#include "Engine/Singleton/TimeSingleton.h"  

using namespace thomasWasLate;  

RotatingPlatform::RotatingPlatform(diji::GameObject* owner, float rotationSpeed)  
   : Component(owner), m_RotationSpeed(rotationSpeed)  
{  
}  

void RotatingPlatform::Init()  
{  
   m_Transform = GetOwner()->GetComponent<diji::Transform>();  
   m_Collider = GetOwner()->GetComponent<diji::Collider>();  
   m_TextureComp = GetOwner()->GetComponent<diji::TextureComp>(); // Ensure m_TextureComp is initialized  

   // Make collider static and stable (no gravity / no bounce)  
   if (m_Collider)  
   {  
       m_Collider->SetStatic(true);  
       m_Collider->SetAffectedByGravity(false);  
       m_Collider->SetRestitution(0.f);  
       m_Collider->SetFriction(1.f);  
   }  

   if (m_TextureComp) {  
       m_TextureComp->SetOrigin({ 100.f, 10.f });  
   }  
}  

void RotatingPlatform::Update()  
{  
   if (!m_Transform) return;  

   const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime();  
   float rotation = m_Transform->GetRotation();  

   // Rotate CCW with W, CW with S  
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))  
       rotation -= m_RotationSpeed * dt;  
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))  
       rotation += m_RotationSpeed * dt;  

   m_Transform->SetRotation(rotation);  

   if (m_TextureComp) {  
       m_TextureComp->SetRotationAngle(rotation);  
   }  
}

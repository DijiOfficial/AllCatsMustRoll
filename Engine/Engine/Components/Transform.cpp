#include "Transform.h"

#include "../Collision/Collider.h"
#include "../Core/GameObject.h"

void diji::Transform::Init()
{
    m_ColliderCompPtr = GetOwner()->GetComponent<Collider>();
}

void diji::Transform::SetPosition(const sf::Vector2f pos)
{
    m_Position = pos;

    if (m_ColliderCompPtr)
        m_ColliderCompPtr->SetNewPosition(m_Position);
}

void diji::Transform::Seek(const float speed)
{
    sf::Vector2f direction =  m_Target->GetPosition() - m_Position;

    if (direction == sf::Vector2f{ 0, 0 })
        return;

    direction = direction.normalized();
    const sf::Vector2f newPosition = m_Position + direction * speed * m_TimeSingleton.GetDeltaTime();

    SetPosition(newPosition);
}

void diji::Transform::SetTarget(const GameObject* target)
{
    m_Target = target->GetComponent<Transform>();
}

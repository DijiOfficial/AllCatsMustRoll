#include "Paddle.h"

#include "Engine/Components/ShapeRender.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/Engine.h"

void pong::Paddle::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_RightBound = window::VIEWPORT.x - GetOwner()->GetComponent<diji::ShapeRender>()->GetShape().getLocalBounds().size.x;
}

void pong::Paddle::Update()
{
    if (m_IsMovingLeft == m_IsMovingRight)
        return;

    const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime();
    const float newX = m_TransformCompPtr->GetPosition().x + (m_IsMovingLeft ? m_Speed * -dt : m_Speed * dt);

    if (newX >= m_LeftBound && newX <= m_RightBound)
    {
        m_TransformCompPtr->AddOffset(m_IsMovingLeft ? m_Speed * -dt : m_Speed * dt, 0);
    }
}

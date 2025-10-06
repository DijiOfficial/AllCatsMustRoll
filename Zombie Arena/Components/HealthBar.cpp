#include "HealthBar.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Components/ShapeRender.h"

void zombieArena::HealthBar::Init()
{
    m_RectRenderCompPtr = GetOwner()->GetComponent<diji::ShapeRender>();
    // m_RectRenderCompPtr->GetRectangle().setSize(sf::Vector2f(static_cast<float>(300), HEALTH_BAR_HEIGHT));
}

void zombieArena::HealthBar::UpdateHealthBar(const int health) const
{
    (void)health;
    // m_RectRenderCompPtr->GetRectangle().setSize(sf::Vector2f(static_cast<float>(health * 3), HEALTH_BAR_HEIGHT));
}

#include "CircRender.h"

#include "TextureComp.h"
#include "../Core/Renderer.h"
#include "Transform.h"
#include "../Core/GameObject.h"
#include "../Collision/Collider.h"

diji::CircRender::CircRender(GameObject* ownerPtr, const bool isDebug)
    : Render(ownerPtr)
    , m_IsDebug{ isDebug }
    , m_NeedsUpdate{ isDebug }
{
}

void diji::CircRender::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<Transform>();
}

void diji::CircRender::RenderFrame() const
{
    if (m_IsDebug)
        GetOwner()->GetComponent<Render>()->RenderFrame();
    
    if (not m_Render)
        return;

    m_CircleShape.setPosition(m_TransformCompPtr->GetPosition());

    Renderer::GetInstance().DrawCirc(m_CircleShape, m_OutlineColor, m_FillColor, m_LineWidth);
}

void diji::CircRender::Update()
{
    if (m_NeedsUpdate)
        SetDrawCollision();
}

void diji::CircRender::SetDrawCollision()
{
    m_NeedsUpdate = false;
    
    

    m_Render = true;
}


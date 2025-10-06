// RotatingPlatform.h
#pragma once
#include "Engine/Components/Component.h"

namespace diji {
    class GameObject;
    class Transform;
    class Collider;
    class TextureComp;
}

namespace thomasWasLate
{
    class RotatingPlatform final : public diji::Component
    {
    public:
        explicit RotatingPlatform(diji::GameObject* owner, float rotationSpeed = 100.f);
        ~RotatingPlatform() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}
        void OnDisable() override {}
        void OnDestroy() override {}

    private:
        float m_RotationSpeed = 100.f;
        diji::Transform* m_Transform = nullptr; // cached in Init
        diji::Collider* m_Collider = nullptr; // optional, set static/no-bounce

        diji::TextureComp* m_TextureComp = nullptr;

    };
}

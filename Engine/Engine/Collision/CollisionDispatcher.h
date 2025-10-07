#pragma once
#include "PhysicsWorld.h"

#include <array>
#include <functional>

namespace diji
{
    class CollisionDispatcher final
    {
    public:
        CollisionDispatcher();
        ~CollisionDispatcher() noexcept = default;

        CollisionDispatcher(const CollisionDispatcher&) = delete;
        CollisionDispatcher& operator=(const CollisionDispatcher&) = delete;
        CollisionDispatcher(CollisionDispatcher&&) noexcept = default;
        CollisionDispatcher& operator=(CollisionDispatcher&&) noexcept = default;
        
        void Dispatch(PhysicsWorld::Prediction& prediction, const Collider* dynamic, const Collider* staticCol) const;

    private:
        using CollisionFunc = std::function<void(PhysicsWorld::Prediction&, const Collider*, const Collider*)>;
            
        // 2D lookup table indexed by shape types
        std::array<std::array<CollisionFunc, 3>, 3> collisionTable_;
            
        static void HandleCircleCircle(PhysicsWorld::Prediction& pred, const Collider* dynamic, const Collider* staticCol);
        static void HandleCircleRect(PhysicsWorld::Prediction& pred, const Collider* dynamic, const Collider* staticCol);
        static void HandleRectRect(PhysicsWorld::Prediction& pred, const Collider* dynamic, const Collider* staticCol);
    };

}

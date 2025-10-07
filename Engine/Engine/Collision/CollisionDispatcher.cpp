#include "CollisionDispatcher.h"
#include "CollisionShape.h"
#include "Collider.h"
#include "CollisionsHelper.h"

diji::CollisionDispatcher::CollisionDispatcher()
{
    // Initialize lookup table
    collisionTable_[static_cast<int>(CollisionShape::ShapeType::CIRCLE)][static_cast<int>(CollisionShape::ShapeType::CIRCLE)] = HandleCircleCircle;
    collisionTable_[static_cast<int>(CollisionShape::ShapeType::CIRCLE)][static_cast<int>(CollisionShape::ShapeType::RECT)] = HandleCircleRect;
    collisionTable_[static_cast<int>(CollisionShape::ShapeType::RECT)][static_cast<int>(CollisionShape::ShapeType::CIRCLE)] = HandleCircleRect;
    collisionTable_[static_cast<int>(CollisionShape::ShapeType::RECT)][static_cast<int>(CollisionShape::ShapeType::RECT)] = HandleRectRect;
    // ... initialize remaining combinations
}

void diji::CollisionDispatcher::Dispatch(PhysicsWorld::Prediction& prediction, const Collider* dynamic, const Collider* staticCol) const
{
    const auto dynamicType = static_cast<int>(dynamic->GetShapeType());
    const auto staticType = static_cast<int>(staticCol->GetShapeType());

    if (const auto handler = collisionTable_[dynamicType][staticType])
        handler(prediction, dynamic, staticCol);
}

void diji::CollisionDispatcher::HandleCircleCircle(PhysicsWorld::Prediction& pred, const Collider* dynamic, const Collider* staticCol)
{
    auto shape = *dynamic_cast<const sf::CircleShape*>(&dynamic->GetShape()->GetShape());
    shape.setPosition(pred.pos);
    const auto otherShape = dynamic_cast<const sf::CircleShape*>(&staticCol->GetShape()->GetShape());
        
    std::vector<PhysicsWorld::CollisionInfo> emptyVec;
    CollisionsHelper::ProcessCircleToCircleCollision(shape, *otherShape, pred.collisionInfoVec, emptyVec);
}

void diji::CollisionDispatcher::HandleCircleRect(PhysicsWorld::Prediction& pred, const Collider* dynamic, const Collider* staticCol)
{
    auto shape = *dynamic_cast<const sf::CircleShape*>(&dynamic->GetShape()->GetShape());
    shape.setPosition(pred.pos);
    const auto otherShape = dynamic_cast<const sf::RectangleShape*>(&staticCol->GetShape()->GetShape());
        
    std::vector<PhysicsWorld::CollisionInfo> emptyVec;
    CollisionsHelper::ProcessCircleToBoxCollision(shape, *otherShape, pred.collisionInfoVec, emptyVec);
}

void diji::CollisionDispatcher::HandleRectRect(PhysicsWorld::Prediction& pred, const Collider* dynamic, const Collider* staticCol)
{
    auto shape = *dynamic_cast<const sf::RectangleShape*>(&dynamic->GetShape()->GetShape());
    shape.setPosition(pred.pos);
    const auto otherShape = dynamic_cast<const sf::RectangleShape*>(&staticCol->GetShape()->GetShape());
        
    std::vector<PhysicsWorld::CollisionInfo> emptyVec;
    CollisionsHelper::ProcessBoxToBoxCollision(shape, *otherShape, pred.collisionInfoVec, emptyVec);
}

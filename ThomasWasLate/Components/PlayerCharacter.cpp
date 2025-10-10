#include "PlayerCharacter.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Collision/Collider.h"
#include "../Singletons/GameManager.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/Transform.h"
#include "Engine/Interfaces/ISoundSystem.h"

thomasWasLate::PlayerCharacter::PlayerCharacter(diji::GameObject* ownerPtr, const CurrentPlayer currPlayer, const float jumpTime)
    : Component{ ownerPtr }
    , m_CurrentCharacter{ currPlayer }
    , m_MaxJumpTime{ jumpTime }
{
}

void thomasWasLate::PlayerCharacter::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();


   
    

    GameManager::GetInstance().OnPlayerSwitchedEvent.AddListener(this, &PlayerCharacter::RefreshView);
    GameManager::GetInstance().OnNewLevelLoadedEvent.AddListener(this, &PlayerCharacter::OnNewLevelLoaded);

}

void thomasWasLate::PlayerCharacter::Start()
{
   m_CameraCompPtr = diji::SceneManager::GetInstance().GetGameObject("A_Camera")->GetComponent<diji::Camera>();
    
    SetCameraFollow();
}

void thomasWasLate::PlayerCharacter::OnTriggerEnter(const diji::Collider* other)
{
    diji::ISoundSystem& soundSystem = diji::ServiceLocator::GetSoundSystem();
    const std::string& tag = other->GetTag();
    
    //Make those sound effect parameters
    std::string audioFile;          //Make audio file string
    constexpr bool isMusic = false; // Its a sound effect so its false
    int volume;                     // 0-100 volume
    
    if (tag == "lava")
    {
        volume = 20;
        audioFile = "sound/lavaouch.wav"; //Location of file
        soundSystem.AddSoundRequest(audioFile, isMusic, volume); //Send a request to play dat sound
        m_TransformCompPtr->SetPosition(m_SpawnPoint); // todo: respawn system resetting velocity and shit
    }

    if (tag == "water")
    {
        volume = 7;
        audioFile = "sound/waterouch.wav"; //Location of file
        soundSystem.AddSoundRequest(audioFile, isMusic, volume); //Send a request to play dat sound
       m_TransformCompPtr->SetPosition(m_SpawnPoint);
        //m_ColliderCompPtr->SetFriction(0.2);//0.2f is default value
       
    }

    if (tag == "goal")
    {
        // level cleared boolean prevents multiple execution (levels were being skipped on completion)
        if (!m_IsLevelCleared)
        {
            m_IsLevelCleared = true;

            GameManager::GetInstance().SetLevelCleared();
            volume = 100;
            audioFile = "sound/finishlevelnya.wav"; //Location of file
            soundSystem.AddSoundRequest(audioFile, isMusic, volume); //Send a request to play dat sound
        }
    }

    if (tag == "void")
    {
        volume = 25;
        audioFile = "sound/bruh.wav"; //Location of file
        soundSystem.AddSoundRequest(audioFile, isMusic, volume); //Send a request to play dat sound
        m_TransformCompPtr->SetPosition(m_SpawnPoint);
    }
}

void thomasWasLate::PlayerCharacter::RefreshView(const bool isSplitscreen) const
{
    if (isSplitscreen)
        diji::SceneManager::GetInstance().SetViewParameters(static_cast<bool>(m_CurrentCharacter) ? 0 : 1, GetOwner()->GetComponent<diji::Transform>(), true, sf::Vector2f{ 25.f, 25.f });
    else
        SetCameraFollow();
}

void thomasWasLate::PlayerCharacter::Move(const sf::Vector2f& direction) const
{
    // will have to figure out how to clamp it
    m_ColliderCompPtr->ApplyForce(direction * m_Speed);

    //Change the speed of the rotation here
    const float rotationSpeed = 5.0f;

    //Amount of rotation calculated based on its direction
    float rotationAmount = direction.x * rotationSpeed;

    //Apply the rotation if Jim is moving
    if (rotationAmount != 0.0f)
    {
        //Send the calculated rotation amoount to AddRotation function
        m_TransformCompPtr->AddRotation(rotationAmount);
    }

}

void thomasWasLate::PlayerCharacter::SetCameraFollow() const
{
    if (m_CurrentCharacter == GameManager::GetInstance().GetCurrentPlayer())
    {
        m_CameraCompPtr->SetFollow(GetOwner());
    }
}

void thomasWasLate::PlayerCharacter::OnNewLevelLoaded()
{
    m_TransformCompPtr->SetPosition(static_cast<sf::Vector2f>(GameManager::GetInstance().GetStartPosition()));

    m_SpawnPoint = m_TransformCompPtr->GetPosition();
}






void thomasWasLate::PlayerCharacter::CheckForBoosting()
{
    // if (m_IsBoosting)
    // {
    //     m_IsBoosting = false;
    //     diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
    //     newCollisionBox.bottom -= GRAVITY * 3 * diji::TimeSingleton::GetInstance().GetDeltaTime();
    //
    //     const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr, newCollisionBox);
    //     for (const auto& collider : colliders)
    //     {
    //         // other collision
    //         if (!collider->GetParent())
    //             continue;
    //
    //         // player collision
    //         if (!collider->GetParent()->HasComponent<PlayerCharacter>())
    //             continue;
    //
    //         collider->GetParent()->GetComponent<PlayerCharacter>()->ClearJump();
    //         const auto& otherBox = collider->GetCollisionBox();
    //         const auto& transform = collider->GetParent()->GetComponent<diji::Transform>();
    //         transform->SetPosition(transform->GetPosition().x, newCollisionBox.bottom - otherBox.height - collider->GetOffset().y + 6.f);
    //     } 
    // }
}

void thomasWasLate::PlayerCharacter::Jump(const bool ignoreTimer)
{
    (void)ignoreTimer;
    // if (!m_IsOnGround)
    //     return;
    //
    // m_IsJumping = true;
    //
    // // Update how long the jump has been going
    // m_JumpTime += diji::TimeSingleton::GetInstance().GetDeltaTime();
    //
    // if (m_JumpTime < m_MaxJumpTime || ignoreTimer)
    // {
    //     diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
    //     newCollisionBox.bottom -= GRAVITY * 3 * diji::TimeSingleton::GetInstance().GetDeltaTime();
    //     
    //     // check for collision with world
    //     if (diji::CollisionSingleton::GetInstance().IsCollidingWithWorld(newCollisionBox))
    //         return;
    //     
    //     // handle collision with players
    //     const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr, newCollisionBox);
    //     for (const auto& collider : colliders)
    //     {
    //         if (ignoreTimer)
    //             break;
    //         
    //         // other collision
    //         if (!collider->GetParent())
    //             continue;
    //     
    //         // player collision
    //         if (collider->GetParent()->HasComponent<PlayerCharacter>())
    //         {
    //             const auto otherBox = collider->GetCollisionBox();
    //             const float myTopEdge = newCollisionBox.bottom;
    //             const float otherBottomEdge = otherBox.bottom + otherBox.height;
    //             if (myTopEdge <= otherBottomEdge)
    //             {
    //                 m_IsBoosting = true;
    //                 collider->GetParent()->GetComponent<PlayerCharacter>()->Jump(true);
    //                 // return;
    //             }
    //         }
    //     }
    //     
    //     m_TransformCompPtr->AddOffset(0.f, -GRAVITY * 3 * diji::TimeSingleton::GetInstance().GetDeltaTime());
    //     return;
    // }
    //
    // CheckForBoosting();
    //
    // m_IsJumping = false;
}

void thomasWasLate::PlayerCharacter::ClearJump()
{
    m_IsOnGround = false;
    m_JumpTime = 5.0f;
    m_IsJumping = false;
    
    CheckForBoosting();
}


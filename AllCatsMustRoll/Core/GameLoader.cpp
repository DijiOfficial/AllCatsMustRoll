#include "GameLoader.h"

#include "GameState.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/FPSCounter.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/ShapeRender.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Singleton/GameStateManager.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Singleton/SceneManager.h"

using namespace diji;

void GameLoader::GameStartUp()
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif


    SceneManager::GetInstance().RegisterScene(static_cast<int>(allCatsMustRoll::allCatsMustRollGameState::StartMenu), MenuTest);
    MenuTest();
}

void GameLoader::MenuTest()
{
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(allCatsMustRoll::allCatsMustRollGameState::StartMenu));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(allCatsMustRoll::allCatsMustRollGameState::StartMenu));
    constexpr sf::IntRect arena{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 1920, 1080 } };


    const auto staticBackground = scene->CreateGameObject("A_StaticBackground");
    staticBackground->AddComponents<Transform>(static_cast<float>(window::VIEWPORT.x) * 0.5f, static_cast<float>(window::VIEWPORT.y) * 0.5f);
    staticBackground->AddComponents<TextureComp>("graphics/background.png");
    staticBackground->AddComponents<Render>();
    scene->SetGameObjectAsStaticBackground(staticBackground);

    const auto camera = scene->CreateCameraObject("A_Camera");
    camera->AddComponents<Transform>(0, 0);
    camera->AddComponents<Camera>(window::VIEWPORT);
    // camera->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));
    camera->GetComponent<Camera>()->SetClampingMode(false);

    // const auto thomas = scene->CreateGameObject("X_Thomas");
    // thomas->AddComponents<Transform>(0, 0);
    // thomas->AddComponents<TextureComp>("graphics/thomas.png");
    // thomas->AddComponents<Render>();
    // // thomas->AddComponents<Collider>(44, 70, sf::Vector2f{ 3.f, 30.f });
    // thomas->AddComponents<thomasWasLate::PlayerCharacter>(0.45f);
    // // thomas->AddComponents<RectRender>(true);

    // const auto testRect = scene->CreateGameObject("X_Testrectll");
    // testRect->AddComponents<Transform>(200, 0);
    // testRect->AddComponents<TextureComp>("graphics/thomas.png");
    // testRect->AddComponents<Render>();
    // testRect->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ 50, 100 });
    // testRect->GetComponent<Collider>()->SetRestitution(0.5f);
    // // testRect->GetComponent<Collider>()->SetAffectedByGravity(false);
    // testRect->AddComponents<thomasWasLate::tempTest>();
    // // testRect->AddComponents<thomasWasLate::PlayerCharacter>(0.45f);
    // testRect->AddComponents<ShapeRender>(true);

    const auto testBall = scene->CreateGameObject("X_TestBall");
    testBall->AddComponents<Transform>(0, 0);
    testBall->AddComponents<TextureComp>("graphics/jim.png");
    testBall->AddComponents<Render>();
    testBall->AddComponents<Collider>(CollisionShape::ShapeType::CIRCLE, 25.f);
    testBall->GetComponent<Collider>()->SetRestitution(0.4f);
    testBall->GetComponent<Collider>()->SetFriction(0.2f);
    // testBall->GetComponent<Collider>()->SetRestitution(0.5f);
    // testBall->AddComponents<thomasWasLate::PlayerCharacter>(0.45f);
    testBall->AddComponents<ShapeRender>(true);

    const auto randomCollider = scene->CreateGameObject("Z_RandomCollider");
    randomCollider->AddComponents<Transform>(RandNumber::GetRandomRangeFloat(-900, 900), RandNumber::GetRandomRangeFloat(-500, 500));
    randomCollider->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ RandNumber::GetRandomRangeFloat(200, 500), RandNumber::GetRandomRangeFloat(15, 50)});
    randomCollider->GetComponent<Collider>()->SetStatic(true);
    randomCollider->GetComponent<Collider>()->GetShape()->SetRotation( sf::Angle{ sf::degrees(RandNumber::GetRandomRangeFloat(0, 360)) });
    randomCollider->AddComponents<ShapeRender>();

    const auto randomCollider2 = scene->CreateGameObject("Z_RandomCollid4er");
    randomCollider2->AddComponents<Transform>(RandNumber::GetRandomRangeFloat(-900, 900), RandNumber::GetRandomRangeFloat(-500, 500));
    randomCollider2->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ RandNumber::GetRandomRangeFloat(200, 500), RandNumber::GetRandomRangeFloat(15, 50)});
    randomCollider2->GetComponent<Collider>()->SetStatic(true);
    randomCollider2->GetComponent<Collider>()->GetShape()->SetRotation(sf::Angle{ sf::degrees(RandNumber::GetRandomRangeFloat(0, 360)) } );
    randomCollider2->AddComponents<ShapeRender>();

    const auto randomCollider3 = scene->CreateGameObject("Z_RandomCol5lider");
    randomCollider3->AddComponents<Transform>(RandNumber::GetRandomRangeFloat(-900, 900), RandNumber::GetRandomRangeFloat(-500, 500));
    randomCollider3->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ RandNumber::GetRandomRangeFloat(200, 500), RandNumber::GetRandomRangeFloat(15, 50)});
    randomCollider3->GetComponent<Collider>()->SetStatic(true);
    randomCollider3->GetComponent<Collider>()->GetShape()->SetRotation(sf::Angle{ sf::degrees(RandNumber::GetRandomRangeFloat(0, 360)) } );
    randomCollider3->AddComponents<ShapeRender>();

    const auto randomCollider4 = scene->CreateGameObject("Z_RandomCol4lider");
    randomCollider4->AddComponents<Transform>(RandNumber::GetRandomRangeFloat(-900, 900), RandNumber::GetRandomRangeFloat(-500, 500));
    randomCollider4->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ RandNumber::GetRandomRangeFloat(200, 500), RandNumber::GetRandomRangeFloat(15, 50)});
    randomCollider4->GetComponent<Collider>()->SetStatic(true);
    randomCollider4->GetComponent<Collider>()->GetShape()->SetRotation(sf::Angle{ sf::degrees(RandNumber::GetRandomRangeFloat(0, 360)) } );
    randomCollider4->AddComponents<ShapeRender>();
    
    const auto tempBoundBottom = scene->CreateGameObject("Z_TempBoundBottom");
    tempBoundBottom->AddComponents<Transform>(0, 514);
    tempBoundBottom->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ 1918, 50 });
    tempBoundBottom->GetComponent<Collider>()->SetStatic(true);
    tempBoundBottom->AddComponents<ShapeRender>();
    
    const auto tempTopBound = scene->CreateGameObject("Z_TempBoundTop");
    tempTopBound->AddComponents<Transform>(0, -514);
    tempTopBound->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ 1918, 50 });
    tempTopBound->GetComponent<Collider>()->SetStatic(true);
    tempTopBound->AddComponents<ShapeRender>();

    const auto tempBoundLeft = scene->CreateGameObject("Z_TempBoundLeft");
    tempBoundLeft->AddComponents<Transform>(-934, 0);
    tempBoundLeft->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ 50, 1078 });
    tempBoundLeft->GetComponent<Collider>()->SetStatic(true);
    tempBoundLeft->AddComponents<ShapeRender>();

    const auto tempBoundRight = scene->CreateGameObject("Z_TempBoundRight");
    tempBoundRight->AddComponents<Transform>(934, 0);
    tempBoundRight->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ 50, 1078 });
    tempBoundRight->GetComponent<Collider>()->SetStatic(true);
    tempBoundRight->AddComponents<ShapeRender>();

    
    // const auto randomCircle = scene->CreateGameObject("Z_TemRoundCirlRight");
    // randomCircle->AddComponents<Transform>(0, 339);
    // randomCircle->AddComponents<Collider>(CollisionShape::ShapeType::CIRCLE, 100.f);
    // randomCircle->GetComponent<Collider>()->SetStatic(true);
    // randomCircle->AddComponents<ShapeRender>();
    
    const auto fpsCounter = scene->CreateGameObject("Z_FPSCounter");
    fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/Roboto-Light.ttf", sf::Color::White, true);
    fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    fpsCounter->AddComponents<FPSCounter>();
    fpsCounter->AddComponents<Transform>(window::VIEWPORT.x - 100, 40);
    fpsCounter->AddComponents<Render>();
    scene->SetGameObjectAsCanvasObject(fpsCounter);
    

    // const auto center = m_Camera->GetCameraView().getCenter();
    // const auto size = m_Camera->GetCameraView().getSize();
    // const auto col = sf::FloatRect{ m_TransformCompPtr->GetPosition(), sf::Vector2f{ 44, 70 } };
    // // const auto col = m_ColliderCompPtr->GetAABB();
    // // const auto offset = m_ColliderCompPtr->GetOffset();
    // const auto offset = sf::Vector2f{ 0.f, 0.f };
    // // bool bounced = false;
    //
    // // Calculate bounds
    // const float leftBound = center.x - size.x * 0.5f;
    // const float rightBound = center.x + size.x * 0.5f - col.width;
    // const float topBound = center.y - size.y * 0.5f;
    // const float bottomBound = center.y + size.y * 0.5f - col.height - offset.y;

    // const auto bob = scene->CreateGameObject("X_Thomas2", thomas);
    // bob->GetComponent<thomasWasLate::PlayerCharacter>()->SetMass(25);
    
#pragma region Commands
    // auto& input = InputManager::GetInstance();

    // input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Key::D, thomas, sf::Vector2f{ 1.f, 0.f });
    // input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Key::A, thomas, sf::Vector2f{ -1.f, 0.f });
    //
    // input.BindCommand<thomasWasLate::CharacterJump>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Key::W, thomas, true);
    // input.BindCommand<thomasWasLate::CharacterJump>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Key::W, thomas, false);

    // input.BindCommand<thomasWasLate::TempAddImpulse>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Key::Space, testBall);
    
#pragma endregion

#pragma region Events

    // zombiesRemainingText->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(pistol->GetComponent<zombieArena::Pistol>(), &zombieArena::Pistol::SaveInfo);
    
#pragma endregion

    
}
#include "GameLoader.h"

#include "GameState.h"
#include "../Components/BackgroundHandler.h"
#include "../Components/PlayerCharacter.h"
#include "../Input/CustomCommands.h"
#include "../Singletons/GameManager.h"
#include "Engine//Collision/Collider.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/ShapeRender.h"
#include "Engine/Components/Sprite.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Core/Engine.h"
#include "Engine/Singleton/GameStateManager.h"
#include "../RotatingPlatform.h" // Corrected the include path to match the directory structure

using namespace diji;

void SceneLoader::GameStartUp()
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif

    //todo: this would be better if it was part of the CreateScene function.
    SceneManager::GetInstance().RegisterScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level), Level);
    Level();
}

void SceneLoader::StartMenu(){}

void SceneLoader::Level()
{
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level));
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(thomasWasLate::thomasWasLateState::Level));

    const auto staticBackground = scene->CreateGameObject("A_StaticBackground");
    staticBackground->AddComponents<Transform>(static_cast<float>(window::VIEWPORT.x) * 0.5f, static_cast<float>(window::VIEWPORT.y) * 0.5f);
    staticBackground->AddComponents<TextureComp>("graphics/background - Copy.png");
    // staticBackground->AddComponents<TextureComp>("graphics/sky.png");
    staticBackground->AddComponents<Render>();
    scene->SetGameObjectAsStaticBackground(staticBackground);

    const auto background = scene->CreateGameObject("B_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<Sprite>("graphics/tiles_sheet.png");
    background->AddComponents<Render>();
    background->AddComponents<thomasWasLate::BackgroundHandler>();
    
    const auto camera = scene->CreateCameraObject("A_Camera");
    camera->AddComponents<Transform>(0, 0);
    camera->AddComponents<Camera>(window::VIEWPORT);
    // camera->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));
    camera->GetComponent<Camera>()->SetClampingMode(false);

    /*const auto thomas = scene->CreateGameObject("X_Thomas");
    thomas->AddComponents<Transform>(0, 0);
    thomas->AddComponents<TextureComp>("graphics/thomas.png");
    thomas->AddComponents<Render>();
    thomas->AddComponents<Collider>(44, 70, sf::Vector2f{ 3.f, 30.f });
    thomas->AddComponents<thomasWasLate::PlayerCharacter>(thomasWasLate::CurrentPlayer::Thomas, 0.45f);
    thomas->AddComponents<RectRender>(true);*/

    /*const auto bob = scene->CreateGameObject("X_Bob");
    bob->AddComponents<Transform>(100, 0);
    bob->AddComponents<TextureComp>("graphics/bob.png");
    bob->AddComponents<Render>();
    bob->AddComponents<Collider>(44, 35, sf::Vector2f{ 3.f, 15.f });
    bob->AddComponents<thomasWasLate::PlayerCharacter>(thomasWasLate::CurrentPlayer::Bob, 0.25f);
    bob->AddComponents<RectRender>(true);*/

    // Create Jim CircleShape
    const auto jim = scene->CreateGameObject("X_Jim");
    jim->AddComponents<Transform>(200, 0);
    jim->AddComponents<TextureComp>("graphics/jim.png");
    jim->AddComponents<Render>();
    jim->AddComponents<Collider>(CollisionShape::ShapeType::CIRCLE, 25.f);
    // jim->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{50, 50});
    jim->GetComponent<Collider>()->SetRestitution(0.4f);
    jim->GetComponent<Collider>()->SetFriction(0.2f);
    // jim->GetComponent<Collider>()->SetAffectedByGravity(false);
    jim->AddComponents<thomasWasLate::PlayerCharacter>(thomasWasLate::CurrentPlayer::Jim, 0.25f);
    jim->AddComponents<ShapeRender>(true);


    //rotating platform object
	const auto platform = scene->CreateGameObject("RotatingPlatform"); // create platform object
	platform->AddComponents<Transform>(400.f, 300.f);// set position
    platform->AddComponents<Collider>(CollisionShape::ShapeType::RECT, sf::Vector2f{ 200.f, 20.f });
    platform->AddComponents<TextureComp>("graphics/platform.png");
    platform->AddComponents<Render>();//
	platform->AddComponents<thomasWasLate::RotatingPlatform>(100.f);// rotate 100 degrees per second




    //Get dat sound system interface
    diji::ISoundSystem& soundSystem = diji::ServiceLocator::GetSoundSystem();

    //Make those sound effect parameters
    const std::string audioFile = "sound/background1.wav"; //Location of file
    const bool isMusic = true; // Its a sound effect so its false
    const int volume = 100;      // 0-100 volume

    //Send a request to play dat sound
    soundSystem.AddSoundRequest(audioFile, isMusic, volume);
   
    
#pragma region Commands
    auto& input = InputManager::GetInstance();

    /*input.BindCommand<thomasWasLate::SwitchSplitScreenView>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::E, nullptr, thomas->GetComponent<thomasWasLate::PlayerCharacter>(), bob->GetComponent<thomasWasLate::PlayerCharacter>());
    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::D, thomas, sf::Vector2f{ 1.f, 0.f });
    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::A, thomas, sf::Vector2f{ -1.f, 0.f });
    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::Right, bob, sf::Vector2f{ 1.f, 0.f });
    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::Left, bob, sf::Vector2f{ -1.f, 0.f });

    input.BindCommand<thomasWasLate::SwitchCharacter>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Q, nullptr);

    input.BindCommand<thomasWasLate::CharacterJump>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::W, thomas, true);
    input.BindCommand<thomasWasLate::CharacterJump>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::W, thomas, false);
    input.BindCommand<thomasWasLate::CharacterJump>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::Up, bob, true);
    input.BindCommand<thomasWasLate::CharacterJump>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Up, bob, false);*/

    //Give input to Jim CircleShape (only left and right movement)
    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::D, jim, sf::Vector2f{ 1.f, 0.f });
    
    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::A, jim, sf::Vector2f{ -1.f, 0.f });
    
#pragma endregion

#pragma region Events

    // zombiesRemainingText->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(pistol->GetComponent<zombieArena::Pistol>(), &zombieArena::Pistol::SaveInfo);
    
#pragma endregion
}
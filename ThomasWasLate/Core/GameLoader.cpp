#include "GameLoader.h"

#include "GameState.h"
#include "../Components/BackgroundHandler.h"
#include "../Components/PlayerCharacter.h"
#include "../Input/CustomCommands.h"
#include "../Singletons/GameManager.h"
#include "Engine/Collision/Collider.h"
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
    thomasWasLate::GameManager& gameManager = thomasWasLate::GameManager::GetInstance();
    

    // Get the paths to the background, tiles and background music
    const std::string& backgroundPath = gameManager.GetBackgroundPath();
    const std::string& tilesetPath = gameManager.GetTilesetPath();
    const std::string& musicPath = gameManager.GetBackgroundMusicPath();

    SceneManager::GetInstance().SetActiveScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level));
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(thomasWasLate::thomasWasLateState::Level));

    gameManager.LoadLevel();

    // Make the background
    const auto staticBackground = scene->CreateGameObject("A_StaticBackground");
    staticBackground->AddComponents<Transform>(static_cast<float>(window::VIEWPORT.x) * 0.5f, static_cast<float>(window::VIEWPORT.y) * 0.5f);
    staticBackground->AddComponents<TextureComp>(backgroundPath);
    staticBackground->AddComponents<Render>();
    scene->SetGameObjectAsStaticBackground(staticBackground);

    // Make the tilesheet
    const auto background = scene->CreateGameObject("B_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<Sprite>(tilesetPath);
    background->AddComponents<Render>();
    background->AddComponents<thomasWasLate::BackgroundHandler>();

    // Make the camera
    const auto camera = scene->CreateCameraObject("A_Camera");
    camera->AddComponents<Transform>(0, 0);
    camera->AddComponents<Camera>(window::VIEWPORT);
    // camera->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));
    camera->GetComponent<Camera>()->SetClampingMode(false);

    // Make Jim (test cat)
    const auto jim = scene->CreateGameObject("X_Jim");
    jim->AddComponents<Transform>(200, 0);
    jim->AddComponents<TextureComp>("graphics/jim.png");
    jim->AddComponents<Render>();
    jim->AddComponents<Collider>(CollisionShape::ShapeType::CIRCLE, 25.f);
    jim->GetComponent<Collider>()->SetRestitution(0.4f);
    jim->GetComponent<Collider>()->SetFriction(0.2f);
    jim->AddComponents<thomasWasLate::PlayerCharacter>(thomasWasLate::CurrentPlayer::Jim, 0.25f);
    jim->AddComponents<ShapeRender>(true);

    // Get the sound system
    diji::ISoundSystem& soundSystem = diji::ServiceLocator::GetSoundSystem();

    // Make the background music
    const bool isMusic = true;
    const int volume = 100;

    //soundSystem.Pause();
    /*TODO: STOP THE PREVIOUS LEVEL'S MUSIC FROM PLAYING WHEN A NEW LEVEL STARTS*/

    soundSystem.AddSoundRequest(musicPath, isMusic, volume);// Play the background music

#pragma region Commands
    auto& input = InputManager::GetInstance();

    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::D, jim, sf::Vector2f{ 1.f, 0.f });

    input.BindCommand<thomasWasLate::MoveCharacter>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::A, jim, sf::Vector2f{ -1.f, 0.f });

#pragma endregion

#pragma region Events

#pragma endregion
}



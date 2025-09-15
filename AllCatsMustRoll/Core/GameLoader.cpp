#include "GameLoader.h"

#include "GameState.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Singleton/GameStateManager.h"
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

    const auto background = scene->CreateGameObject("A_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<TextureComp>("graphics/background.png");
    background->AddComponents<Render>();
    background->AddComponents<Camera>(1920.f, 1080.f);
    background->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));
    
}
#include "GameManager.h"

#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>


#include "../Core/GameState.h"
// #include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/ShapeRender.h"
#include "Engine/Singleton/GameStateManager.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/Transform.h"
#include <iostream>

/*void thomasWasLate::GameManager::SwitchPlayer()
{
    m_CurrentPlayer = static_cast<bool>(m_CurrentPlayer) ? CurrentPlayer::Thomas : CurrentPlayer::Bob;

    OnPlayerSwitchedEvent.Broadcast();
}*/

void thomasWasLate::GameManager::LoadLevel()
{
    ReadLevelInfo(LoadInformation());

    CreateWorldCollision();

   OnNewLevelLoadedEvent.Broadcast();
}

void thomasWasLate::GameManager::SetLevelCleared()
{
    // Go to the next level if there is one 
    if (m_CurrentLevel < m_LevelConfigs.size())
    {
        ++m_CurrentLevel;
    }
    else // When all levels are done
    {
        
        // todo: game finish screen
        std::cout << "GAME IS FINISHED"<< std::endl;
    }
    

    OnNewLevelLoadedEvent.ClearListeners();
    OnPlayerSwitchedEvent.ClearListeners();
    diji::SceneManager::GetInstance().SetNextSceneToActivate(static_cast<int>(thomasWasLateState::Level));
    std::cout << "LEVEL" << m_CurrentLevel << " LOADED" << std::endl;
}



std::string thomasWasLate::GameManager::LoadInformation()
{
    
   // Check if the current level is valid (unlikley it is invalid but, better safe than sorry ig)
   if (m_CurrentLevel <= 0 || m_CurrentLevel > m_LevelConfigs.size())
   {
       throw std::runtime_error("Invalid current level index.");
       
   }
   
   // Get the starting position for the jim (player)
   const auto& currentPos = m_LevelConfigs.at(m_CurrentLevel - 1);
   m_StartPosition = currentPos.startPos;

    // Return the level text file of the current level (if the game hasn't been beaten yet)
    return m_LevelConfigs.at(m_CurrentLevel - 1).levelText;
    
}

void thomasWasLate::GameManager::ReadLevelInfo(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        // Extra error details becuase runtime errors are slayy
        std::cerr << "Failed to open file: " << filepath << "\n";
        std::cerr << "Absolute path: " << std::filesystem::absolute(filepath) << "\n";
        throw std::runtime_error("Could not open level file: " + filepath);
    }
        

    std::string line;
    m_Rows = 0;
    m_Cols = 0;
    m_LevelInfo = std::vector<int>();

    while (std::getline(file, line))
    {
        int colCount = 0;

        for (const char c : line)
        {
            if (std::isdigit(c))
            {
                int number = c - '0';
                m_LevelInfo.push_back(number);
                ++colCount;
            }
        }

        if (m_Rows == 0)
            m_Cols = colCount;

        ++m_Rows;
    }

    
    file.close();
}

void thomasWasLate::GameManager::CreateWorldCollision() const
{
    constexpr float kTileSize = 50.0f;

    // Clear previously created tagged colliders for tiles 2/3/4
    // m_TileColliders = std::vector<std::unique_ptr<diji::Collider>>();
    
    for (int row = 0; row < m_Rows; ++row)
    {
        int col = 0;
        while (col < m_Cols)
        {
            const int idx = row * m_Cols + col;
            const int tile = m_LevelInfo[idx];

            if (tile == 1)
            {
                const int startC = col;
                while (col < m_Cols && m_LevelInfo[row * m_Cols + col] == 1)
                    ++col;

                const int len = col - startC;

                const float left = static_cast<float>(startC) * kTileSize;
                const float bottom = static_cast<float>(row) * kTileSize;
                const float width  = static_cast<float>(len) * kTileSize;
                constexpr float height = kTileSize;
                
                sf::Vector2f center{ left + width * 0.5f, bottom + height * 0.5f };

                auto tempBound = std::make_unique<diji::GameObject>();
                tempBound->AddComponents<diji::Transform>(center);
                tempBound->AddComponents<diji::Collider>(diji::CollisionShape::ShapeType::RECT, sf::Vector2f{ static_cast<float>(len) * kTileSize, kTileSize });
                tempBound->GetComponent<diji::Collider>()->SetStatic(true);
                // tempBound->AddComponents<diji::ShapeRender>();

                (void)diji::SceneManager::GetInstance().SpawnGameObject("WorldCollider", std::move(tempBound), center);
            }
            else
            {
                // Create individual colliders for special tiles 2/3/4 with tags
                if (tile == 2 || tile == 3 || tile == 4)
                {
                    const float left = static_cast<float>(col) * kTileSize;
                    const float bottom = static_cast<float>(row) * kTileSize;
                    constexpr float width  = kTileSize;
                    constexpr float height = kTileSize;
                
                    sf::Vector2f center{ left + width * 0.5f, bottom + height * 0.5f };

                    // todo: set up overlap event collisions!
                    auto tempBound = std::make_unique<diji::GameObject>();
                    tempBound->AddComponents<diji::Transform>(center);
                    tempBound->AddComponents<diji::Collider>(diji::CollisionShape::ShapeType::RECT, sf::Vector2f{ width, height });
                    const auto collider = tempBound->GetComponent<diji::Collider>();
                    collider->SetStatic(true);
                    collider->SetCollisionResponse(diji::Collider::CollisionResponse::Overlap);

                    // tempBound->AddComponents<diji::ShapeRender>();
                   
                    switch (tile)
                    {
                    case 2:
                        collider->SetTag("lava");
                        break;
                    case 3:
                        collider->SetTag("water");
                        break;
                    case 4:
                        collider->SetTag("goal");
                        break;
                    default:
                        break;
                    }
                    
                    diji::SceneManager::GetInstance().SpawnGameObject("WorldCollider", std::move(tempBound), center);
                }
                ++col;
            }
        }

        if (row == m_Rows - 1)
        {
            const float width  = static_cast<float>(m_Cols) * 1.5f * kTileSize;
            const float left = -static_cast<float>(m_Cols) * kTileSize * 0.5f;
            const float bottom = static_cast<float>(row + 2) * kTileSize;
            constexpr float height = kTileSize;
            
            sf::Vector2f center{ left + width * 0.5f, bottom + height * 0.5f };

            auto tempBound = std::make_unique<diji::GameObject>();
            tempBound->AddComponents<diji::Transform>(center);
            tempBound->AddComponents<diji::Collider>(diji::CollisionShape::ShapeType::RECT, sf::Vector2f{ width, height });
            // tempBound->AddComponents<diji::ShapeRender>();
            
            const auto collider = tempBound->GetComponent<diji::Collider>();
            collider->SetStatic(true);
            collider->SetCollisionResponse(diji::Collider::CollisionResponse::Overlap);
            collider->SetTag("void");
            
            (void)diji::SceneManager::GetInstance().SpawnGameObject("WorldCollider", std::move(tempBound), center);
        }
    }

   
}

#pragma once
#include "Engine/Interfaces/EventSystem.h"
#include "Engine/Singleton/Singleton.h"

#include <string>
#include <SFML/System/Vector2.hpp>
#include <stdexcept>
#include <iostream>


namespace thomasWasLate
{
    enum class CurrentPlayer
    {
        Jim = 0,
        John
    };

    //struct for each level
    struct LevelConfig
    {
        //Every level has a different text file, background, tileset, music, volume and start position
        std::string levelText;
        std::string backgroundImg;
        std::string tilesetImg;
        std::string backgroundMusic;
        int musicVol;
        sf::Vector2f startPos;

    };

    class GameManager final : public diji::Singleton<GameManager>
    {
    public:
        [[nodiscard]] CurrentPlayer GetCurrentPlayer() const { return m_CurrentPlayer; }
        //void SwitchPlayer();

        diji::Event<> OnPlayerSwitchedEvent;
        diji::Event<> OnNewLevelLoadedEvent;
        void LoadLevel();
        void ClearLevelInfo() { m_LevelInfo = std::vector<int>(); }
        [[nodiscard]] const std::vector<int>& GetLevelInfo() const { return m_LevelInfo; }
        [[nodiscard]] const sf::Vector2f& GetStartPosition() const { return m_StartPosition; }
        // [[nodiscard]] int GetCurrentLevel() const { return m_CurrentLevel; }
        [[nodiscard]] int GetRows() const { return m_Rows; }
        [[nodiscard]] int GetCols() const { return m_Cols; }
        void SetLevelCleared();


        //Get the path to the background file
        [[nodiscard]] const std::string& GetBackgroundPath() const
        {
            // -1 is used becuase a vector starts at 0
            return m_LevelConfigs.at(m_CurrentLevel - 1).backgroundImg;
        }

        //Get the path to the tileset file
        [[nodiscard]] const std::string& GetTilesetPath() const
        {
            
            // -1 is used becuase a vector starts at 0
            return m_LevelConfigs.at(m_CurrentLevel - 1).tilesetImg;
        }

        //Get the path to the background music file
        [[nodiscard]] const std::string& GetBackgroundMusicPath() const
        {

            // -1 is used becuase a vector starts at 0
            return m_LevelConfigs.at(m_CurrentLevel - 1).backgroundMusic;
        }

        //Get the path to the volume value
        [[nodiscard]] const int GetVolume() const
        {

            // -1 is used becuase a vector starts at 0
            return m_LevelConfigs.at(m_CurrentLevel - 1).musicVol;
        }

    private:
        // std::vector<std::unique_ptr<diji::Collider>> m_TileColliders;
        CurrentPlayer m_CurrentPlayer = CurrentPlayer::Jim;
        sf::Vector2f m_StartPosition;
        std::vector<int> m_LevelInfo;


        

        //A vector (list) of every level config
        std::vector<LevelConfig> m_LevelConfigs =
        {

           {// Level 1
                .levelText = "Resources/levels/level1.txt",
                .backgroundImg = "graphics/background1.jpg",
                .tilesetImg = "graphics/tiles1.png",
                .backgroundMusic = "sound/background1.mp3",
                .musicVol = 100,
                .startPos = {225, 0}
           },

            {// Level 2
                .levelText = "Resources/levels/level2.txt",
                .backgroundImg = "graphics/background2.jpg",
                .tilesetImg = "graphics/tiles2.png",
                .backgroundMusic = "sound/background2.wav",
                .musicVol = 100,
                .startPos = {225, 0}
            },

            {// Level 3
                .levelText = "Resources/levels/level3.txt",
                .backgroundImg = "graphics/background3.jpg",
                .tilesetImg = "graphics/tiles3.png",
                .backgroundMusic = "sound/background3.wav",
                .musicVol = 75,
                .startPos = {225, 0}
            },
            
            {// Level 4
                .levelText = "Resources/levels/level4.txt",
                .backgroundImg = "graphics/background4.jpg",
                .tilesetImg = "graphics/tiles4.png",
                .backgroundMusic = "sound/background4.wav",
                .musicVol = 50,
                .startPos = {225, 0}
            }
            // Extra levels can easily be added here
        };



        int m_CurrentLevel = 1;
        int m_Rows = 0;
        int m_Cols = 0;
        float m_LevelTimeLimit = 0.0f;

        std::string LoadInformation();
        void ReadLevelInfo(const std::string& filepath);
        void CreateWorldCollision() const;
    };
}

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "core/GameObject.h"
#include "entities/Marble.h"
#include "levels/Level.h"

#include <vector>

enum class GameState {
    PLAYING,
    LEVEL_CLEARED,
    GAME_OVER,
    GAME_COMPLETED
};

/**
 * @class GameManager
 * @brief Orquesta el ciclo de vida del juego, la progresión de niveles y el HUD.
 */
class GameManager {
private:
    std::vector<Level*> levels;
    int currentLevelIndex;
    GameState state;

    Marble* playerMarble;
    std::vector<GameObject*> activeWorldEntities;

    int lives;
    int totalScore;
    float levelTimer;
    float totalTimer;
    float messageTimer;
    float levelTransitionTimer;
    float gameOverTimer;

    void RebuildWorldEntities();

public:
    GameManager();
    ~GameManager();

    void Init();
    void LoadLevel(int index);
    void NextLevel();
    void RestartCurrentLevel();
    void RestartGame();

    void Update(float dt);
    void Draw3D();
    void DrawHUD();

    // Acceso a la canica para la cámara
    Marble* GetPlayerMarble() const { return playerMarble; }
};

#endif // GAMEMANAGER_H

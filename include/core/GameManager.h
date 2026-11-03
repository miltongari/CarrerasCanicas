#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "core/GameObject.h"
#include "entities/Marble.h"
#include "levels/Level.h"

#include <vector>

enum class GameState {
    PLAYING,
    LEVEL_CLEARED,
    GAME_COMPLETED
};

/**
 * @class GameManager
 * @brief Orquesta el ciclo de vida del juego, la progresión de niveles y el HUD.
 *
 * DIDÁCTICA POO:
 * Demuestra Composición de alto nivel: gestiona la colección de niveles (Level*),
 * el jugador (Marble*) y la lista polimórfica homogénea (GameObject*) para el renderizado.
 */
class GameManager {
private:
    std::vector<Level*> levels;
    int currentLevelIndex;
    GameState state;

    Marble* playerMarble;
    std::vector<GameObject*> activeWorldEntities;

    int totalScore;
    float levelTimer;
    float totalTimer;
    float messageTimer;
    float levelTransitionTimer;

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

#include "core/GameManager.h"
#include "levels/Level1.h"
#include "levels/Level2.h"
#include "levels/Level3.h"

GameManager::GameManager()
    : currentLevelIndex(0),
      state(GameState::PLAYING),
      playerMarble(nullptr),
      lives(3),
      totalScore(0),
      levelTimer(0.0f),
      totalTimer(0.0f),
      messageTimer(0.0f),
      levelTransitionTimer(0.0f),
      gameOverTimer(0.0f) {}

GameManager::~GameManager() {
    delete playerMarble;
    playerMarble = nullptr;

    for (Level* lvl : levels) {
        delete lvl;
    }
    levels.clear();
    activeWorldEntities.clear();
}

void GameManager::Init() {
    // 1. Instanciamos los 3 niveles con polimorfismo
    Level* l1 = new Level1();
    l1->Build();
    levels.push_back(l1);

    Level* l2 = new Level2();
    l2->Build();
    levels.push_back(l2);

    Level* l3 = new Level3();
    l3->Build();
    levels.push_back(l3);

    // 2. Instanciamos la canica del jugador
    playerMarble = new Marble(levels[0]->GetStartPosition(), 0.5f, MAROON);

    // 3. Cargamos el primer nivel
    LoadLevel(0);
}

void GameManager::RebuildWorldEntities() {
    activeWorldEntities.clear();

    // La canica es la primera entidad polimórfica
    if (playerMarble) {
        activeWorldEntities.push_back(playerMarble);
    }

    // El nivel en curso añade sus plataformas, monedas y meta al vector de renderizado
    if (currentLevelIndex >= 0 && currentLevelIndex < static_cast<int>(levels.size())) {
        levels[currentLevelIndex]->PopulateEntities(activeWorldEntities);
    }
}

void GameManager::LoadLevel(int index) {
    if (index < 0 || index >= static_cast<int>(levels.size())) return;

    currentLevelIndex = index;
    state = GameState::PLAYING;
    lives = 3; // Cada nivel cuenta con 3 vidas
    levelTimer = 0.0f;
    messageTimer = 0.0f;
    gameOverTimer = 0.0f;

    // Ajustar canica a la salida del nuevo nivel
    playerMarble->SetStartPosition(levels[currentLevelIndex]->GetStartPosition());
    playerMarble->Reset();

    // Reconstruir entidades activas para el renderizado
    RebuildWorldEntities();
}

void GameManager::NextLevel() {
    if (currentLevelIndex + 1 < static_cast<int>(levels.size())) {
        LoadLevel(currentLevelIndex + 1);
    } else {
        state = GameState::GAME_COMPLETED;
    }
}

void GameManager::RestartCurrentLevel() {
    levels[currentLevelIndex]->ResetCoinsAndGoal();
    playerMarble->Reset();
    lives = 3;
    levelTimer = 0.0f;
    state = GameState::PLAYING;
    messageTimer = 0.0f;
    gameOverTimer = 0.0f;
}

void GameManager::RestartGame() {
    totalScore = 0;
    totalTimer = 0.0f;
    for (Level* lvl : levels) {
        lvl->ResetCoinsAndGoal();
    }
    LoadLevel(0);
}

void GameManager::Update(float dt) {
    if (messageTimer > 0.0f) {
        messageTimer -= dt;
    }

    Level* currentLevel = levels[currentLevelIndex];

    if (state == GameState::PLAYING) {
        totalTimer += dt;
        levelTimer += dt;

        // Actualización polimórfica del jugador y del nivel
        playerMarble->Update(dt);
        currentLevel->Update(dt);

        // Física y colisiones
        currentLevel->CheckCollisions(playerMarble);
        currentLevel->CheckCoinPickups(playerMarble, totalScore);

        // Detección de caída al vacío
        if (currentLevel->CheckFall(playerMarble)) {
            lives--;
            if (lives > 0) {
                playerMarble->Reset();
                messageTimer = 1.8f;
            } else {
                // Se acabaron las 3 vidas del nivel
                state = GameState::GAME_OVER;
                gameOverTimer = 2.0f; // Dura 2 segundos antes de reiniciar al nivel 1
            }
        }

        // Detección de llegada a la meta
        if (currentLevel->CheckGoal(playerMarble)) {
            if (currentLevelIndex == static_cast<int>(levels.size()) - 1) {
                state = GameState::GAME_COMPLETED;
            } else {
                state = GameState::LEVEL_CLEARED;
                levelTransitionTimer = 2.5f;
            }
        }
    } else if (state == GameState::LEVEL_CLEARED) {
        levelTransitionTimer -= dt;
        if (levelTransitionTimer <= 0.0f || IsKeyPressed(KEY_ENTER)) {
            NextLevel();
        }
    } else if (state == GameState::GAME_OVER) {
        // Mensaje de fin de partida: espera 2 segundos y reinicia al nivel 1
        gameOverTimer -= dt;
        if (gameOverTimer <= 0.0f) {
            RestartGame();
        }
    } else if (state == GameState::GAME_COMPLETED) {
        if (IsKeyPressed(KEY_ENTER)) {
            RestartGame();
        }
    }
}

void GameManager::Draw3D() {
    // POLIMORFISMO DE RENDERIZADO:
    // Dibujamos canica, plataformas, obstáculos móviles y coleccionables homogéneamente
    for (GameObject* entity : activeWorldEntities) {
        if (entity->IsActive()) {
            entity->Draw();
        }
    }
}

void GameManager::DrawHUD() {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // 1. Panel de estado superior
    DrawRectangle(20, 20, 360, 140, ColorAlpha(BLACK, 0.75f));
    DrawRectangleLines(20, 20, 360, 140, GOLD);

    DrawText("MARBLE RUNNER 3D", 35, 30, 20, YELLOW);
    DrawText(levels[currentLevelIndex]->GetName().c_str(), 35, 54, 16, SKYBLUE);
    DrawText(TextFormat("Puntaje Total: %d pts", totalScore), 35, 76, 16, RAYWHITE);
    DrawText(TextFormat("Tiempo Nivel:  %.2f s", levelTimer), 35, 96, 16, RAYWHITE);

    // Indicador visual de Vidas (3 vidas por nivel)
    DrawText("Vidas:", 35, 116, 16, RAYWHITE);
    for (int i = 0; i < 3; i++) {
        Color marbleColor = (i < lives) ? RED : DARKGRAY;
        DrawCircle(95 + (i * 22), 125, 7, marbleColor);
        DrawCircleLines(95 + (i * 22), 125, 7, (i < lives) ? WHITE : GRAY);
    }
    DrawText(TextFormat("(%d / 3)", lives), 168, 116, 16, (lives <= 1 ? RED : (lives == 2 ? YELLOW : GREEN)));

    DrawText("Controles: [W][A][S][D] Mover | [ESPACIO] Salto", 35, 140, 11, LIGHTGRAY);

    // 2. Alerta de caída al vacío (cuando aún quedan vidas)
    if (messageTimer > 0.0f && state == GameState::PLAYING) {
        DrawRectangle(screenWidth / 2 - 210, 90, 420, 50, ColorAlpha(RED, 0.85f));
        DrawRectangleLines(screenWidth / 2 - 210, 90, 420, 50, WHITE);
        const char* fallText = TextFormat("¡CAÍSTE AL VACÍO! Te queda%s %d vida%s",
                                          (lives == 1 ? "" : "n"), lives, (lives == 1 ? "" : "s"));
        DrawText(fallText, screenWidth / 2 - MeasureText(fallText, 19) / 2, 105, 19, WHITE);
    }

    // 3. Cartel de GAME OVER ("Buen intento" durante 2 segundos)
    if (state == GameState::GAME_OVER) {
        DrawRectangle(screenWidth / 2 - 220, screenHeight / 2 - 75, 440, 150, ColorAlpha(BLACK, 0.92f));
        DrawRectangleLines(screenWidth / 2 - 220, screenHeight / 2 - 75, 440, 150, RED);

        const char* gameOverTitle = "Buen intento";
        DrawText(gameOverTitle, screenWidth / 2 - MeasureText(gameOverTitle, 36) / 2, screenHeight / 2 - 45, 36, RED);

        const char* resetNotice = "Reiniciando al Nivel 1...";
        DrawText(resetNotice, screenWidth / 2 - MeasureText(resetNotice, 20) / 2, screenHeight / 2 + 15, 20, RAYWHITE);
    }

    // 4. Cartel de Nivel Superado (Transición)
    if (state == GameState::LEVEL_CLEARED) {
        DrawRectangle(screenWidth / 2 - 250, screenHeight / 2 - 100, 500, 170, ColorAlpha(DARKBLUE, 0.90f));
        DrawRectangleLines(screenWidth / 2 - 250, screenHeight / 2 - 100, 500, 170, LIME);

        DrawText("¡NIVEL COMPLETADO!", screenWidth / 2 - 165, screenHeight / 2 - 75, 26, LIME);
        DrawText(TextFormat("Tiempo del nivel: %.2f s", levelTimer), screenWidth / 2 - 120, screenHeight / 2 - 30, 20, RAYWHITE);
        DrawText("Cargando siguiente nivel...", screenWidth / 2 - 120, screenHeight / 2 + 5, 18, YELLOW);
        DrawText("Presiona [ENTER] para saltar", screenWidth / 2 - 110, screenHeight / 2 + 35, 14, GRAY);
    }

    // 5. Cartel de Gran Victoria (Juego Terminado)
    if (state == GameState::GAME_COMPLETED) {
        DrawRectangle(screenWidth / 2 - 280, screenHeight / 2 - 120, 560, 220, ColorAlpha(BLACK, 0.92f));
        DrawRectangleLines(screenWidth / 2 - 280, screenHeight / 2 - 120, 560, 220, GOLD);

        DrawText("¡CAMPEÓN DE MARBLE RUNNER!", screenWidth / 2 - 210, screenHeight / 2 - 95, 26, GOLD);
        DrawText("¡Has superado los 3 niveles!", screenWidth / 2 - 140, screenHeight / 2 - 55, 18, RAYWHITE);
        DrawText(TextFormat("PUNTAJE FINAL: %d PUNTOS", totalScore), screenWidth / 2 - 145, screenHeight / 2 - 15, 22, YELLOW);
        DrawText(TextFormat("TIEMPO TOTAL:  %.2f SEGUNDOS", totalTimer), screenWidth / 2 - 150, screenHeight / 2 + 18, 20, LIME);
        DrawText("Presiona [ENTER] para volver a jugar", screenWidth / 2 - 160, screenHeight / 2 + 60, 17, ORANGE);
    }
}

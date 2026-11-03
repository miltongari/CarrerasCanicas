#include "core/GameManager.h"
#include "levels/Level1.h"
#include "levels/Level2.h"
#include "levels/Level3.h"

GameManager::GameManager()
    : currentLevelIndex(0),
      state(GameState::PLAYING),
      playerMarble(nullptr),
      totalScore(0),
      levelTimer(0.0f),
      totalTimer(0.0f),
      messageTimer(0.0f),
      levelTransitionTimer(0.0f) {}

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
    levelTimer = 0.0f;
    messageTimer = 0.0f;

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
    levelTimer = 0.0f;
    state = GameState::PLAYING;
    messageTimer = 0.0f;
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
    // Botón / atajo para reiniciar al Nivel 1 (mediante clic o tecla [1])
    Rectangle btnRestartLevel1 = { 20, 155, 200, 36 };
    Vector2 mousePos = GetMousePosition();
    bool btnHovered = CheckCollisionPointRec(mousePos, btnRestartLevel1);

    if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1) || (btnHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
        RestartGame();
        return;
    }

    // Controles globales: reiniciar nivel actual con [R]
    if (IsKeyPressed(KEY_R)) {
        RestartCurrentLevel();
        return;
    }

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
            playerMarble->Reset();
            messageTimer = 1.8f;
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
    DrawRectangle(20, 20, 360, 125, ColorAlpha(BLACK, 0.70f));
    DrawRectangleLines(20, 20, 360, 125, GOLD);

    DrawText("SUPER MONKEY MARBLE 3D", 35, 30, 20, YELLOW);
    DrawText(levels[currentLevelIndex]->GetName().c_str(), 35, 55, 17, SKYBLUE);
    DrawText(TextFormat("Puntaje Total: %d pts", totalScore), 35, 80, 17, RAYWHITE);
    DrawText(TextFormat("Tiempo Nivel:  %.2f s", levelTimer), 35, 102, 17, RAYWHITE);
    DrawText("Controles: [W][A][S][D] | [ESPACIO] Salto | [R] Reset", 35, 126, 10, LIGHTGRAY);

    // Botón interactivo en pantalla: Reiniciar al Nivel 1
    Rectangle btnRestartLevel1 = { 20, 155, 200, 36 };
    Vector2 mousePos = GetMousePosition();
    bool btnHovered = CheckCollisionPointRec(mousePos, btnRestartLevel1);

    Color btnColor = btnHovered ? ColorAlpha(DARKBLUE, 0.90f) : ColorAlpha(BLACK, 0.75f);
    DrawRectangleRec(btnRestartLevel1, btnColor);
    DrawRectangleLinesEx(btnRestartLevel1, 2.0f, btnHovered ? YELLOW : GOLD);
    DrawText("↺ Reiniciar Nivel 1 [1]", 35, 164, 15, btnHovered ? YELLOW : RAYWHITE);

    // 2. Alerta de caída al vacío
    if (messageTimer > 0.0f && state == GameState::PLAYING) {
        DrawRectangle(screenWidth / 2 - 200, 90, 400, 50, ColorAlpha(RED, 0.85f));
        DrawRectangleLines(screenWidth / 2 - 200, 90, 400, 50, WHITE);
        DrawText("¡CAÍSTE AL VACÍO! Reapareciendo...", screenWidth / 2 - 175, 105, 19, WHITE);
    }

    // 3. Cartel de Nivel Superado (Transición)
    if (state == GameState::LEVEL_CLEARED) {
        DrawRectangle(screenWidth / 2 - 250, screenHeight / 2 - 100, 500, 170, ColorAlpha(DARKBLUE, 0.90f));
        DrawRectangleLines(screenWidth / 2 - 250, screenHeight / 2 - 100, 500, 170, LIME);

        DrawText("¡NIVEL COMPLETADO!", screenWidth / 2 - 165, screenHeight / 2 - 75, 26, LIME);
        DrawText(TextFormat("Tiempo del nivel: %.2f s", levelTimer), screenWidth / 2 - 120, screenHeight / 2 - 30, 20, RAYWHITE);
        DrawText("Cargando siguiente nivel...", screenWidth / 2 - 120, screenHeight / 2 + 5, 18, YELLOW);
        DrawText("Presiona [ENTER] para saltar", screenWidth / 2 - 110, screenHeight / 2 + 35, 14, GRAY);
    }

    // 4. Cartel de Gran Victoria (Juego Terminado)
    if (state == GameState::GAME_COMPLETED) {
        DrawRectangle(screenWidth / 2 - 280, screenHeight / 2 - 120, 560, 220, ColorAlpha(BLACK, 0.92f));
        DrawRectangleLines(screenWidth / 2 - 280, screenHeight / 2 - 120, 560, 220, GOLD);

        DrawText("¡CAMPEÓN DE MONKEY MARBLE!", screenWidth / 2 - 220, screenHeight / 2 - 95, 26, GOLD);
        DrawText("¡Has superado los 3 niveles difíciles!", screenWidth / 2 - 170, screenHeight / 2 - 55, 18, RAYWHITE);
        DrawText(TextFormat("PUNTAJE FINAL: %d PUNTOS", totalScore), screenWidth / 2 - 145, screenHeight / 2 - 15, 22, YELLOW);
        DrawText(TextFormat("TIEMPO TOTAL:  %.2f SEGUNDOS", totalTimer), screenWidth / 2 - 150, screenHeight / 2 + 18, 20, LIME);
        DrawText("Presiona [ENTER] para volver a jugar", screenWidth / 2 - 160, screenHeight / 2 + 60, 17, ORANGE);
    }
}

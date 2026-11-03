#include "raylib.h"
#include "raymath.h"
#include "core/GameManager.h"

int main() {
    // 1. Inicialización de ventana y contexto gráfico Raylib
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Marble Runner 3D");
    SetTargetFPS(60);

    // 2. Inicialización del gestor de juego (GameManager)
    GameManager gameManager;
    gameManager.Init();

    // 3. Configuración de la Cámara 3D (Tercera persona suave)
    Camera3D camera{};
    Marble* player = gameManager.GetPlayerMarble();
    camera.position = (Vector3){ player->GetPosition().x, player->GetPosition().y + 5.0f, player->GetPosition().z + 8.0f };
    camera.target   = player->GetPosition();
    camera.up       = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy     = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 camOffset = { 0.0f, 4.8f, 8.0f };

    // 4. Bucle principal del juego (Game Loop)
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // A) Actualización de la lógica del juego
        gameManager.Update(dt);

        // B) Suavizado dinámico de la cámara hacia la posición actual de la canica
        Vector3 marblePos = player->GetPosition();
        Vector3 targetCamPos = (Vector3){
            marblePos.x + camOffset.x,
            marblePos.y + camOffset.y,
            marblePos.z + camOffset.z
        };

        float camSpeed = 6.5f;
        camera.position.x += (targetCamPos.x - camera.position.x) * camSpeed * dt;
        camera.position.y += (targetCamPos.y - camera.position.y) * camSpeed * dt;
        camera.position.z += (targetCamPos.z - camera.position.z) * camSpeed * dt;
        camera.target = marblePos;

        // C) Renderizado 3D y 2D
        BeginDrawing();
            ClearBackground((Color){ 20, 24, 38, 255 }); // Azul oscuro espacial / arcade

            BeginMode3D(camera);
                // Cuadrícula de referencia en el vacío
                DrawGrid(100, 2.0f);

                // Renderizado polimórfico de todas las entidades
                gameManager.Draw3D();
            EndMode3D();

            // Renderizado de interfaz gráfica 2D (HUD)
            gameManager.DrawHUD();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

#include "entities/Platform.h"
#include <cmath>

Platform::Platform(Vector3 pos, Vector3 platformSize, Color col)
    : GameObject(pos, col),
      size(platformSize),
      initialPos(pos),
      moveDirection({ 0.0f, 0.0f, 0.0f }),
      moveDistance(0.0f),
      moveSpeed(0.0f),
      moveTimer(0.0f) {}

Platform::Platform(Vector3 pos, Vector3 platformSize, Color col,
                   Vector3 moveDir, float moveDist, float speed)
    : GameObject(pos, col),
      size(platformSize),
      initialPos(pos),
      moveDirection(moveDir),
      moveDistance(moveDist),
      moveSpeed(speed),
      moveTimer(0.0f) {}

void Platform::Update(float dt) {
    if (!active) return;

    // Si tiene movimiento configurado, aplicamos oscilación senoidal
    if (moveDistance > 0.001f) {
        moveTimer += dt * moveSpeed;
        float offset = sinf(moveTimer) * moveDistance;
        position.x = initialPos.x + (moveDirection.x * offset);
        position.y = initialPos.y + (moveDirection.y * offset);
        position.z = initialPos.z + (moveDirection.z * offset);
    }
}

void Platform::Draw() {
    if (!active) return;

    // Dibujamos el prisma sólido
    DrawCube(position, size.x, size.y, size.z, color);

    // Contorno estético para visualizar bordes y profundidad en 3D
    Color wireColor = (moveDistance > 0.001f) ? RED : DARKGRAY;
    DrawCubeWires(position, size.x, size.y, size.z, wireColor);
}

BoundingBox Platform::GetBoundingBox() const {
    BoundingBox box;
    box.min = (Vector3){
        position.x - (size.x / 2.0f),
        position.y - (size.y / 2.0f),
        position.z - (size.z / 2.0f)
    };
    box.max = (Vector3){
        position.x + (size.x / 2.0f),
        position.y + (size.y / 2.0f),
        position.z + (size.z / 2.0f)
    };
    return box;
}

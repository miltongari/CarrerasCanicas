#include "entities/Coin.h"
#include "raymath.h"
#include <cmath>

Coin::Coin(Vector3 pos, float r, int points)
    : GameObject(pos, GOLD),
      radius(r),
      rotationAngle(0.0f),
      rotationSpeed(180.0f), // Rotación veloz y dinámica
      initialY(pos.y),
      bobbingTimer(0.0f),
      pointValue(points) {}

void Coin::Update(float dt) {
    if (!active) return;

    // Giro sobre su eje
    rotationAngle += rotationSpeed * dt;
    if (rotationAngle >= 360.0f) rotationAngle -= 360.0f;

    // Levitación suave
    bobbingTimer += dt;
    position.y = initialY + (sinf(bobbingTimer * 4.0f) * 0.22f);
}

void Coin::Draw() {
    if (!active) return;

    // Disco exterior dorado
    DrawCylinder(position, radius, radius, 0.14f, 16, GOLD);
    DrawCylinderWires(position, radius, radius, 0.14f, 16, ORANGE);

    // Núcleo brillante reflectante
    DrawSphere(position, radius * 0.65f, YELLOW);
}

bool Coin::CheckCollisionWithMarble(Vector3 marblePos, float marbleRadius) {
    if (!active) return false;

    if (CheckCollisionSpheres(position, radius, marblePos, marbleRadius)) {
        active = false; // Desactivar moneda
        return true;
    }
    return false;
}

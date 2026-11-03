#include "entities/Goal.h"
#include "raymath.h"
#include <cmath>

Goal::Goal(Vector3 pos, float r)
    : GameObject(pos, LIME), radius(r), pulseTimer(0.0f), reached(false) {}

void Goal::Update(float dt) {
    pulseTimer += dt;
}

void Goal::Draw() {
    float pulse = sinf(pulseTimer * 5.0f) * 0.18f;
    Color glowColor = reached ? SKYBLUE : ColorAlpha(LIME, 0.75f);

    // Plataforma base circular
    DrawCylinder(position, radius, radius, 0.12f, 28, DARKGREEN);
    DrawCylinderWires(position, radius, radius, 0.12f, 28, GREEN);

    // Anillo exterior brillante
    DrawCylinder((Vector3){ position.x, position.y + 0.06f, position.z },
                 radius * 0.85f, radius * 0.85f, 0.1f, 24, ColorAlpha(YELLOW, 0.85f));

    // Haz o campana de luz traslúcida que vibra
    DrawCylinder((Vector3){ position.x, position.y + 1.8f, position.z },
                 (radius * 0.6f) + pulse, (radius * 0.4f) + pulse, 3.6f, 20, glowColor);
    DrawCylinderWires((Vector3){ position.x, position.y + 1.8f, position.z },
                      (radius * 0.6f) + pulse, (radius * 0.4f) + pulse, 3.6f, 20, WHITE);
}

bool Goal::CheckGoalReached(Vector3 marblePos, float marbleRadius) {
    if (reached) return true;

    float dx = marblePos.x - position.x;
    float dz = marblePos.z - position.z;
    float horizontalDist = sqrtf(dx * dx + dz * dz);
    float dy = fabsf(marblePos.y - position.y);

    if (horizontalDist <= (radius + marbleRadius) && dy <= 1.8f) {
        reached = true;
        return true;
    }
    return false;
}

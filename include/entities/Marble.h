#ifndef MARBLE_H
#define MARBLE_H

#include "core/GameObject.h"
#include "raymath.h"

/**
 * @class Marble
 * @brief Canica controlada por el jugador con física realista de rodamiento 3D (Monkey Ball).
 *
 * DIDÁCTICA:
 * Implementa rotación 3D continua mediante matrices de rotación (Matrix)
 * y ejes de giro derivados del vector de velocidad horizontal:
 * Eje = Vector3CrossProduct(Velocidad, Up).
 */
class Marble : public GameObject {
private:
    Vector3 velocity;
    Vector3 startPosition;
    float radius;
    float acceleration;
    float maxSpeed;
    float friction;
    float gravity;
    bool isGrounded;

    // Matriz de orientación acumulada en 3D para el rodamiento visual
    Matrix rotationMatrix;

public:
    Marble(Vector3 startPos, float r = 0.5f, Color col = MAROON);

    void Update(float dt) override;
    void Draw() override;

    void ResolveBoxCollision(const BoundingBox& box);
    void Reset();

    // Getters y Setters
    float GetRadius() const { return radius; }
    Vector3 GetVelocity() const { return velocity; }
    void SetVelocity(Vector3 newVel) { velocity = newVel; }
    bool IsGrounded() const { return isGrounded; }
    void SetGrounded(bool grounded) { isGrounded = grounded; }
    Vector3 GetStartPosition() const { return startPosition; }
    void SetStartPosition(Vector3 newStart) { startPosition = newStart; }
};

#endif // MARBLE_H

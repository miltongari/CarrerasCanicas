#ifndef PLATFORM_H
#define PLATFORM_H

#include "core/GameObject.h"

/**
 * @class Platform
 * @brief Representa plataformas estáticas o móviles tipo Super Monkey Ball.
 */
class Platform : public GameObject {
private:
    Vector3 size;           // Ancho (X), Alto/Grosor (Y), Profundidad (Z)
    Vector3 initialPos;     // Posición de anclaje para plataformas móviles
    Vector3 moveDirection;  // Eje de movimiento normalizado (ej. {1,0,0})
    float moveDistance;     // Amplitud máxima del vaivén
    float moveSpeed;        // Velocidad angular del movimiento
    float moveTimer;        // Acumulador de tiempo para la función senoidal

public:
    // Constructor estándar para plataformas estáticas
    Platform(Vector3 pos, Vector3 platformSize, Color col = LIGHTGRAY);

    // Sobrecarga de constructor para plataformas móviles (Monkey Ball hazards)
    Platform(Vector3 pos, Vector3 platformSize, Color col,
             Vector3 moveDir, float moveDist, float speed);

    void Update(float dt) override;
    void Draw() override;

    BoundingBox GetBoundingBox() const;

    Vector3 GetSize() const { return size; }
};

#endif // PLATFORM_H

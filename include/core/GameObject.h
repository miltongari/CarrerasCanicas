#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"

/**
 * @class GameObject
 * @brief Clase base abstracta para todas las entidades del mundo 3D.
 *
 * CONCEPTOS DIDÁCTICOS DE POO:
 * 1. Abstracción: Define el contrato común (Update y Draw).
 * 2. Encapsulamiento: Atributos protegidos con métodos accesores.
 * 3. Polimorfismo: Métodos virtuales puros (= 0) y destructor virtual.
 */
class GameObject {
protected:
    Vector3 position;
    Color color;
    bool active;

public:
    GameObject(Vector3 startPosition, Color startColor = WHITE)
        : position(startPosition), color(startColor), active(true) {}

    virtual ~GameObject() = default;

    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;

    Vector3 GetPosition() const { return position; }
    void SetPosition(Vector3 newPos) { position = newPos; }

    Color GetColor() const { return color; }
    void SetColor(Color newColor) { color = newColor; }

    bool IsActive() const { return active; }
    void SetActive(bool newState) { active = newState; }
};

#endif // GAMEOBJECT_H

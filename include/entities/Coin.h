#ifndef COIN_H
#define COIN_H

#include "core/GameObject.h"

/**
 * @class Coin
 * @brief Coleccionable brillante que gira y levita en el escenario.
 */
class Coin : public GameObject {
private:
    float radius;
    float rotationAngle;
    float rotationSpeed;
    float initialY;
    float bobbingTimer;
    int pointValue;

public:
    Coin(Vector3 pos, float r = 0.35f, int points = 10);

    void Update(float dt) override;
    void Draw() override;

    bool CheckCollisionWithMarble(Vector3 marblePos, float marbleRadius);

    float GetRadius() const { return radius; }
    int GetValue() const { return pointValue; }
};

#endif // COIN_H

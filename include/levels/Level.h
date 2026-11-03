#ifndef LEVEL_H
#define LEVEL_H

#include "core/GameObject.h"
#include "entities/Platform.h"
#include "entities/Coin.h"
#include "entities/Goal.h"
#include "entities/Marble.h"

#include <vector>
#include <string>

/**
 * @class Level
 * @brief Clase base abstracta para los niveles de juego.
 *
 * DIDÁCTICA POO:
 * Cada nivel concreto (Level1, Level2, Level3) hereda de esta clase
 * e implementa su método virtual puro Build().
 */
class Level {
protected:
    std::string name;
    Vector3 startPosition;
    float fallLimitY;
    std::vector<Platform*> platforms;
    std::vector<Coin*> coins;
    Goal* goal;

public:
    Level(const std::string& levelName, Vector3 startPos, float fallLimit = -10.0f);
    virtual ~Level();

    // Método virtual puro: cada nivel construye su geometría específica
    virtual void Build() = 0;

    // Actualiza plataformas móviles y monedas
    virtual void Update(float dt);

    // Exporta todas las entidades al vector polimórfico de renderizado
    void PopulateEntities(std::vector<GameObject*>& entities);

    // Física y colisiones del nivel con la canica
    void CheckCollisions(Marble* marble);
    void CheckCoinPickups(Marble* marble, int& score);
    bool CheckGoal(Marble* marble);
    bool CheckFall(Marble* marble);
    void ResetCoinsAndGoal();

    // Getters
    std::string GetName() const { return name; }
    Vector3 GetStartPosition() const { return startPosition; }
    Goal* GetGoal() const { return goal; }
};

#endif // LEVEL_H

#ifndef LEVEL2_H
#define LEVEL2_H

#include "levels/Level.h"

/**
 * @class Level2
 * @brief Nivel 2: "El Desfiladero Veloz"
 * Pendiente pronunciada de gran aceleración, curva cerrada y plataforma móvil cruzando el vacío.
 */
class Level2 : public Level {
public:
    Level2();
    void Build() override;
};

#endif // LEVEL2_H

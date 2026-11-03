#ifndef LEVEL3_H
#define LEVEL3_H

#include "levels/Level.h"

/**
 * @class Level3
 * @brief Nivel 3: "La Espiral del Vértigo"
 * Dificultad extrema estilo Super Monkey Ball Master: Islas flotantes,
 * obstáculos móviles de barrido, saltos al vacío y plataforma final diminuta.
 */
class Level3 : public Level {
public:
    Level3();
    void Build() override;
};

#endif // LEVEL3_H

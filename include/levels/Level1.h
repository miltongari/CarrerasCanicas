#ifndef LEVEL1_H
#define LEVEL1_H

#include "levels/Level.h"

/**
 * @class Level1
 * @brief Nivel 1: "Pradera de Equilibrio"
 * Curvas cerradas y tablón de equilibrio estrecho tipo Super Monkey Ball.
 */
class Level1 : public Level {
public:
    Level1();
    void Build() override;
};

#endif // LEVEL1_H

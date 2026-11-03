#ifndef GOAL_H
#define GOAL_H

#include "core/GameObject.h"

/**
 * @class Goal
 * @brief Portal de meta estilo arco/baliza de Super Monkey Ball.
 */
class Goal : public GameObject {
private:
    float radius;
    float pulseTimer;
    bool reached;

public:
    Goal(Vector3 pos, float r = 1.8f);

    void Update(float dt) override;
    void Draw() override;

    bool CheckGoalReached(Vector3 marblePos, float marbleRadius);

    bool IsReached() const { return reached; }
    void Reset() { reached = false; }
};

#endif // GOAL_H

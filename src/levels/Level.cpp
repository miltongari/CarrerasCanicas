#include "levels/Level.h"

Level::Level(const std::string& levelName, Vector3 startPos, float fallLimit)
    : name(levelName), startPosition(startPos), fallLimitY(fallLimit), goal(nullptr) {}

Level::~Level() {
    // Liberación polimórfica de la memoria de las entidades del nivel
    for (Platform* p : platforms) delete p;
    platforms.clear();

    for (Coin* c : coins) delete c;
    coins.clear();

    if (goal) {
        delete goal;
        goal = nullptr;
    }
}

void Level::Update(float dt) {
    for (Platform* p : platforms) {
        p->Update(dt);
    }
    for (Coin* c : coins) {
        c->Update(dt);
    }
    if (goal) {
        goal->Update(dt);
    }
}

void Level::PopulateEntities(std::vector<GameObject*>& entities) {
    for (Platform* p : platforms) entities.push_back(p);
    for (Coin* c : coins) entities.push_back(c);
    if (goal) entities.push_back(goal);
}

void Level::CheckCollisions(Marble* marble) {
    if (!marble) return;
    for (Platform* p : platforms) {
        if (p->IsActive()) {
            marble->ResolveBoxCollision(p->GetBoundingBox());
        }
    }
}

void Level::CheckCoinPickups(Marble* marble, int& score) {
    if (!marble) return;
    for (Coin* c : coins) {
        if (c->IsActive() && c->CheckCollisionWithMarble(marble->GetPosition(), marble->GetRadius())) {
            score += c->GetValue();
        }
    }
}

bool Level::CheckGoal(Marble* marble) {
    if (!marble || !goal) return false;
    return goal->CheckGoalReached(marble->GetPosition(), marble->GetRadius());
}

bool Level::CheckFall(Marble* marble) {
    if (!marble) return false;
    return marble->GetPosition().y < fallLimitY;
}

void Level::ResetCoinsAndGoal() {
    for (Coin* c : coins) {
        c->SetActive(true);
    }
    if (goal) {
        goal->Reset();
    }
}

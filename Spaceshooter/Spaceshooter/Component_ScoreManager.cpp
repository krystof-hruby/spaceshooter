// Component_ScoreManager.cpp
// Krystof Hruby
// 2023

#include "Component_ScoreManager.h"

bool Component_ScoreManager::ReachedGoal() const {
    return score >= this->goal;
}

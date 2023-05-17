// ActiveBounds.cpp
// Krystof Hruby
// 2023

#include "ActiveBounds.h"

const float ActiveBounds::RIGHT = 5000;
const float ActiveBounds::LEFT = -5000;
const float ActiveBounds::TOP = 5000;
const float ActiveBounds::BOTTOM = -5000;

bool ActiveBounds::IsInBounds(Vector2D position) {
    if (position.XValue > ActiveBounds::RIGHT)
        return false;
    else if (position.XValue < ActiveBounds::LEFT)
        return false;
    else if (position.YValue > ActiveBounds::TOP)
        return false;
    else if (position.YValue < ActiveBounds::BOTTOM)
        return false;

    return true;
}

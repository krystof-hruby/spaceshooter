// Global.cpp
// Krystof Hruby
// 2023

#include "Global.h"

double Time::delta_time;

const float ActiveBounds::RIGHT = 1000;
const float ActiveBounds::LEFT = -1000;
const float ActiveBounds::TOP = 1000;
const float ActiveBounds::BOTTOM = -1000;

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

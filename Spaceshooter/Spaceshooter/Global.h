// Global.h
// Krystof Hruby
// 2023

#pragma once

#include "vector2D.h"

// DEBUGGING:

#ifndef LOGGING_ENABLED
	#define LOGGING_ENABLED true
#endif

#ifndef VISUALIZE_HITBOXES
	#define VISUALIZE_HITBOXES false
#endif

// GLOBAL VALUES:
const float SECOND = 1.0f;
const float PI = 3.14f;

// Provides delta time.
class Time final {
public:
	// Provides delta time between last two frames.
	static double delta_time;
};

// Screen bounds for active game objects.
// Deactivate game objects if out of these bounds.
class ActiveBounds final {
public:
	static const float LEFT;
	static const float RIGHT;
	static const float TOP;
	static const float BOTTOM;

	// Returns true if given position is in active bounds.
	static bool IsInBounds(Vector2D position);
};
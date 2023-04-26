// ActiveBounds.h
// Krystof Hruby
// 2023

#pragma once

#include "vector2D.h"

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

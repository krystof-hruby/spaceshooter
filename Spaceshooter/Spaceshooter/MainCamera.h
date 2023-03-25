// MainCamera.h
// Krystof Hruby
// 2023

#pragma once

#include "mydrawengine.h"

// Manages the game camera's position and zoom
class MainCamera final {
public:
	// Move camera to this position.
	void MoveTo(Vector2D position) const;
	// Set the camera's zoom.
	void Zoom(float zoom) const;
};


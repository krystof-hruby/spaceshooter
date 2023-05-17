// MainCamera.cpp
// Krystof Hruby
// 2023

#include "MainCamera.h"

void MainCamera::MoveTo(Vector2D position) const {
	MyDrawEngine::GetInstance()->theCamera.PlaceAt(position);
}

void MainCamera::Zoom(float zoom) const {
	MyDrawEngine::GetInstance()->theCamera.SetZoom(zoom);
}

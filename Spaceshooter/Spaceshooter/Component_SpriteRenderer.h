// Component_SpriteRenderer.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "mydrawengine.h"

// String with L prefix.
typedef const wchar_t* Sprite;

// Draws image onto the screen based on values from transform.
class Component_SpriteRenderer : public Component {
private:
	PictureIndex image = 0;

public:
	using Component::Component;

	float transparency = 0;
	
	void SetSprite(Sprite sprite);
	void UnsetSprite();

	void Update();
};


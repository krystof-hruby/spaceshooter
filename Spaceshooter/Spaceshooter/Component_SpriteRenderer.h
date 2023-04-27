// Component_SpriteRenderer.h
// Krystof Hruby
// 2023

#pragma once

#include "Component.h"
#include "mydrawengine.h"

// String with L prefix. Path to sprite location.
typedef const wchar_t* Sprite;

// Draws image onto the screen based on values from transform.
class Component_SpriteRenderer final : public Component {
private:
	PictureIndex image = 0;

public:
	using Component::Component;

	// Value from 0 to 1 (not transparent to fully transparent).
	float transparency = 0;
	
	// Changes the sprite.
	void SetSprite(Sprite sprite);
	// Removes any sprites.
	void UnsetSprite();

	inline bool Startable() const override { return false; }
	void Update() override;
};


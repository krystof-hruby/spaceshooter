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
	Component_SpriteRenderer(std::shared_ptr<GameObject> game_object);
	Component_SpriteRenderer(std::shared_ptr<GameObject> game_object, Sprite sprite);

	float transparency = 0;
	
	void ChangeSprite(Sprite sprite);
	void Start();
	void Update();
};


// Component_SpriteRenderer.cpp
// Krystof Hruby
// 2023

#include "Component_SpriteRenderer.h"

#include "GameObject.h"
#include "Component_Transform.h"

void Component_SpriteRenderer::SetSprite(Sprite sprite) {
	this->image = MyDrawEngine::GetInstance()->LoadPicture(sprite);
}

void Component_SpriteRenderer::UnsetSprite() {
	if (!this->image) // No image
		return;

	MyDrawEngine::GetInstance()->ReleasePicture(this->image);
}

void Component_SpriteRenderer::Update() {
	if (!this->image) // No image
		return;

	// Update sprite position, scale and rotation.
	Vector2D position = this->game_object->GetComponent<Component_Transform>()->position;
	float scale = this->game_object->GetComponent<Component_Transform>()->scale;
	float rotation = this->game_object->GetComponent<Component_Transform>()->rotation;

	// Draw sprite on the screen.
	MyDrawEngine::GetInstance()->DrawAt(position, this->image, scale, rotation, this->transparency);
}
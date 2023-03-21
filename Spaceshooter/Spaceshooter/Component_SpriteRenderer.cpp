// Component_SpriteRenderer.cpp
// Krystof Hruby
// 2023

#include "Component_SpriteRenderer.h"

#include "GameObject.h"

Component_SpriteRenderer::Component_SpriteRenderer(std::shared_ptr<GameObject> game_object) : Component(game_object) { }

Component_SpriteRenderer::Component_SpriteRenderer(std::shared_ptr<GameObject> game_object, Sprite sprite) : Component(game_object) {
	this->ChangeSprite(sprite);
}

void Component_SpriteRenderer::ChangeSprite(Sprite sprite) {
	this->image = MyDrawEngine::GetInstance()->LoadPicture(sprite);
}

void Component_SpriteRenderer::Start() { }

void Component_SpriteRenderer::Update() {
	if (!this->image) // No image
		return;

	Vector2D position = this->game_object->GetComponent<Component_Transform>()->position;
	float scale = this->game_object->GetComponent<Component_Transform>()->scale;
	float rotation = this->game_object->GetComponent<Component_Transform>()->rotation;

	MyDrawEngine::GetInstance()->DrawAt(position, this->image, scale, rotation, this->transparency);
}
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

	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	MyDrawEngine::GetInstance()->DrawAt(transform->position, this->image, transform->scale, transform->rotation, this->transparency);
}
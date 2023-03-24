// Component_Animator.cpp
// Krystof Hruby
// 2023

#include "Component_Animator.h"

#include <exception>

#include "GameObject.h"
#include "Global.h"
#include "Component_Transform.h"

// Animation:

Animation::Animation(std::string name, std::vector<Sprite> sprites, bool loop, float speed) {
	this->name = name;

	if (sprites.size() <= 0)
		throw std::exception("Animation must have at least 1 frame.");

	for (int i = 0; i < sprites.size(); i++)
		this->frames->push_back(MyDrawEngine::GetInstance()->LoadPicture(sprites[i]));

	this->loop = loop;
	this->speed = speed;
}

bool Animation::Play(Vector2D position, float scale, float rotation) {
	if (this->animation_time >= (1 / this->speed))
		this->current_frame++;

	if (this->current_frame >= this->frames->size()) { // End of the animation.
		if (!this->loop)
			return true; // No loop.
		
		this->Reset(); // Loop.
	}
	
	MyDrawEngine::GetInstance()->DrawAt(position, (*this->frames)[this->current_frame], scale, rotation);

	// Called every frame. Increase by delta time.
	this->animation_time += (float)Time::delta_time;
}

void Animation::Reset() {
	this->current_frame = 0;
	this->animation_time = 0;
}


// Component_Animator:

void Component_Animator::RegisterAnimation(std::shared_ptr<Animation> animation) {
	if (this->animations[animation->name])
		throw new std::exception("Cannot register animation. Animation under this name already registered.");
	
	this->animations[animation->name] = animation;
}

void Component_Animator::PlayAnimation(std::string animation_name) {
	if (!this->animations[animation_name])
		throw new std::exception("Cannot play animation. Animation under this name not found");
	
	this->current_animation = this->animations[animation_name];
	this->current_animation->Reset();
}

void Component_Animator::ModifyAnimation(std::string animation_name, bool loop, float speed) {
	if (!this->animations[animation_name])
		throw new std::exception("Cannot modify animation. Animation under this name not found");

	this->animations[animation_name]->loop = loop;
	this->animations[animation_name]->speed = speed;
}

void Component_Animator::Update() {
	if (!this->current_animation)
		return;

	// Get animation position, scale and rotation.
	Vector2D position = this->game_object->GetComponent<Component_Transform>()->position;
	float scale = this->game_object->GetComponent<Component_Transform>()->scale;
	float rotation = this->game_object->GetComponent<Component_Transform>()->rotation;

	if (this->current_animation->Play(position, scale, rotation))
		this->current_animation = nullptr; // Do not recalculate anything for finished animations.
}

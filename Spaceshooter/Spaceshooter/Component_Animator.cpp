// Component_Animator.cpp
// Krystof Hruby
// 2023

#include "Component_Animator.h"

#include "Component_Transform.h"
#include "Constants.h"
#include "GameObject.h"
#include "ImageRenderer.h"
#include "Time.h"

// Animation:

Animation::Animation(std::string name, std::vector<Sprite> sprites, int layer, bool loop, double speed) {
	this->name = name;

	if (sprites.size() <= 0)
		throw EngineException("Cannot create animation. Animation must have at least one frame.");

	for (int i = 0; i < sprites.size(); i++)
		this->animation_frames->push_back(MyDrawEngine::GetInstance()->LoadPicture(sprites[i]));

	this->layer = layer;
	this->loop = loop;
	this->speed = speed;
}

void Animation::Play(Vector2D position, float scale, float rotation) {
	if (this->frame_time >= (SECOND / this->speed)) {
		this->current_frame++;
		this->frame_time = 0; // Reset frame time.
	}

	if (this->current_frame >= this->animation_frames->size()) { // End of the animation.
		if (!this->loop)
			return; // No loop. Animation finished.
		
		this->Reset(); // Loop.
	}

	ImageRenderer::GetInstance().ScheduleImage((*this->animation_frames)[this->current_frame], this->layer, position, scale, rotation, this->transparency);

	this->frame_time += Time::delta_time;
	this->elapsed_time += Time::delta_time;
}

void Animation::Reset() {
	this->current_frame = 0;
	this->frame_time = 0;
	this->elapsed_time = 0;
}

double Animation::GetElapsedTime() const {
	return this->elapsed_time;
}

bool Animation::IsFinished() const {
	return !this->loop && (this->current_frame == this->animation_frames->size());
}


// Component_Animator:

void Component_Animator::Update() {
	if (!this->current_animation)
		return;

	auto transform = this->GetGameObject()->GetComponent<Component_Transform>();
	this->current_animation->Play(transform->position, transform->scale, transform->rotation);

	if (this->current_animation->IsFinished())
		this->StopAnimation(); // Do not recalculate anything for finished animations.
}

void Component_Animator::LoadAnimation(std::shared_ptr<Animation> animation) {
	if (this->animations[animation->name])
		throw EngineException("Cannot register animation. Animation under the name: " + animation->name + " already registered.");
	
	this->animations[animation->name] = animation;
}

void Component_Animator::PlayAnimation(std::string animation_name) {
	if (!this->animations[animation_name])
		throw EngineException("Cannot play animation. Animation under the name: " + animation_name + " not found.");
	
	this->current_animation = this->animations[animation_name];
	this->current_animation->Reset();
}

void Component_Animator::StopAnimation() {
	this->current_animation = nullptr;
}

bool Component_Animator::AnimationFinished(std::string animation_name) {
	if (!this->animations[animation_name])
		throw EngineException("Cannot modify animation. Animation under the name: " + animation_name + " not found.");

	return this->animations[animation_name]->IsFinished();
}

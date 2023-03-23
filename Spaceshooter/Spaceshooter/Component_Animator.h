// Component_Animator.h
// Krystof Hruby
// 2023

#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "Component_SpriteRenderer.h" // For Sprite (besides Component).
#include "mydrawengine.h"

// Holds information about animation.
class Animation : public Identifiable {
private:
	std::shared_ptr<std::vector<PictureIndex>> frames;
	int current_frame = 0;
	float animation_time = 0;

public:
	Animation(std::string name, std::vector<Sprite> sprites, bool loop = false, float speed = 1);

	// Name of the animation.
	std::string name;

	// Whether to loop the animation.
	bool loop = false;

	// Animation frames per second.
	float speed = 1;

	// Plays the animation. Returns true when finished (never true if loopable).
	bool Play(Vector2D position, float scale, float rotation);

	// Reset animation to begin from the start again.
	void Reset();
};

// Enables animation.
class Component_Animator : public Component {
private:
	// All animations stored in this component.
	std::unordered_map<std::string, std::shared_ptr<Animation>> animations;

	// Currently played animation.
	std::shared_ptr<Animation> current_animation;

public:
	using Component::Component;

	// Registered animation can be played by their name.
	void RegisterAnimation(std::shared_ptr<Animation> animation);

	// Play animation registered with this name.
	void PlayAnimation(std::string animation_name);

	// Modify values of animation registered with this name. May produce unpredictable results if modified wile playing.
	void ModifyAnimation(std::string animation_name, bool loop, float speed);

	void Update() override final;
};


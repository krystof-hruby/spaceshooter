// Component_Animator.h
// Krystof Hruby
// 2023

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Component_SpriteRenderer.h" // For Sprite (besides Component).
#include "mydrawengine.h"

// Holds information about animation.
class Animation final : public Identifiable {
private:
	// Sprites in the order to be played.
	std::shared_ptr<std::vector<PictureIndex>> animation_frames = std::make_shared<std::vector<PictureIndex>>();
	
	// Currently shown animation frame.
	int current_frame = 0;
	
	// Elapsed time of currently shown frame.
	double frame_time = 0;

	// Elapsed time of the animation.
	double elapsed_time = 0;

public:
	Animation(std::string name, std::vector<Sprite> sprites, bool loop = false, double speed = 1);

	// Name of the animation.
	std::string name;

	// Whether to loop the animation.
	bool loop = false;

	// Animation frames per second.
	double speed = 1;

	// Returns time elapsed from the start of the animation.
	double GetElapsedTime() const;

	bool IsFinished() const;

	// Plays the animation. Returns true when finished (never true if loopable).
	bool Play(Vector2D position, float scale, float rotation);

	// Reset animation to begin from the start again.
	void Reset();
};

// Enables animation.
class Component_Animator final : public Component {
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

	// Stops any currently played animation.
	void StopAnimation();

	// Modify values of animation registered with this name. May produce unpredictable results if modified wile playing.
	void ModifyAnimation(std::string animation_name, bool loop, double speed);

	// Modify values of animation registered with this name. May produce unpredictable results if modified wile playing.
	void ModifyAnimation(std::string animation_name, bool loop);

	// Modify values of animation registered with this name. May produce unpredictable results if modified wile playing.
	void ModifyAnimation(std::string animation_name, double speed);

	// Whether the animation has finished.
	bool AnimationFinished(std::string animation_name);

	inline bool Startable() const override { return false; }
	void Update() override;
};


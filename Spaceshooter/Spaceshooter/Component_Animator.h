// Component_Animator.h
// Krystof Hruby
// 2023

#pragma once

#include <unordered_map>
#include "Component_SpriteRenderer.h" // For Sprite (besides Component).

// Holds information about animation.
class Animation final : public Identifiable {
public:
	Animation(std::string name, std::vector<Sprite> sprites, int layer = 0, bool loop = false, double speed = 1);

	// Name of the animation.
	std::string name;

	// Whether to loop the animation.
	bool loop = false;

	// Animation frames per second.
	double speed = 1;

	// 0 = not transparent. 1 = fully transparent.
	float transparency = 0;

	// Rendering layer in which the image will be drawn. Higher layers are drawn on top of lower layers.
	int layer = 0;

	// Returns time elapsed from the start of the animation.
	double GetElapsedTime() const;

	bool IsFinished() const;

	// Plays the animation. Returns true when finished (never true if loopable).
	void Play(Vector2D position, float scale = 1, float rotation = 0);

	// Reset animation to begin from the start again.
	void Reset();

private:
	// Sprites in the order to be played.
	std::shared_ptr<std::vector<PictureIndex>> animation_frames = std::make_shared<std::vector<PictureIndex>>();

	// Currently shown animation frame.
	int current_frame = 0;

	// Elapsed time of currently shown frame.
	double frame_time = 0;

	// Elapsed time of the animation.
	double elapsed_time = 0;

};

// Enables animation.
class Component_Animator final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	void Update() override;

	// Registered animation can be played by their name.
	void RegisterAnimation(std::shared_ptr<Animation> animation);

	// Play animation registered with this name.
	void PlayAnimation(std::string animation_name);

	// Stops any currently played animation.
	void StopAnimation();

	// Whether the animation has finished.
	bool AnimationFinished(std::string animation_name);

private:
	// All animations stored in this component.
	std::unordered_map<std::string, std::shared_ptr<Animation>> animations;

	// Currently played animation.
	std::shared_ptr<Animation> current_animation;
};


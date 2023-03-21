// Component_SoundEmitter.cpp
// Krystof Hruby
// 2023

#include "Component_SoundEmitter.h"

Component_SoundEmitter::Component_SoundEmitter(std::shared_ptr<GameObject> game_object, std::vector<Sound> sounds) : Component(game_object) {
	// Load all sounds playable by this object.
	for (auto sound : sounds) {
		this->sounds[sound] = MySoundEngine::GetInstance()->LoadWav(sound);
	}
}

void Component_SoundEmitter::Play(Sound sound, bool loop) {
	// Do not play sound if not loaded.
	if (this->sounds.find(sound) == this->sounds.end())
		return;

	MySoundEngine::GetInstance()->Play(this->sounds[sound], loop);
}

void Component_SoundEmitter::Stop(Sound sound) {
	// Do not stop sound if not loaded.
	if (this->sounds.find(sound) == this->sounds.end())
		return;
	
	MySoundEngine::GetInstance()->Stop(this->sounds[sound]);
}

void Component_SoundEmitter::Start() { }

void Component_SoundEmitter::Update() { }
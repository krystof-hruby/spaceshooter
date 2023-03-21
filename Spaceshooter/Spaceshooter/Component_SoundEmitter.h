// Component_SoundEmitter.h
// Krystof Hruby
// 2023

#pragma once

#include <unordered_map>
#include <vector>

#include "Component.h"
#include "mysoundengine.h"

typedef const wchar_t* Sound;

// Enables playing sounds. All sounds must be loaded first.
class Component_SoundEmitter : public Component {
private:
	std::unordered_map<Sound, SoundIndex> sounds;

public:
	Component_SoundEmitter(std::shared_ptr<GameObject> game_object, std::vector<Sound> sounds);

	void Play(Sound sound, bool loop = false);
	void Stop(Sound sound);

	void Start();
	void Update();
};


// Component_SoundEmitter.h
// Krystof Hruby
// 2023

#pragma once

#include <unordered_map>
#include "Component.h"
#include "mysoundengine.h"

// String with L prefix. Path to audio clip location.
typedef const wchar_t* AudioClip;

// Enables playing audio. All audio clips should be loaded before played for the first time.
class Component_AudioEmitter final : public Component {
public:
	using Component::Component;
	inline bool Startable() const override { return false; }
	inline bool Updatable() const override { return false; }

	// Audio clip should be loaded before played for the first time.
	void Load(AudioClip audio_clip);
	// Audio clips should be loaded before played for the first time.
	void Load(std::vector<AudioClip> audio_clips);

	// Will load audio clip if not loaded.
	void Play(AudioClip audio_clip, bool loop = false);
	// Play all audio clips.
	void Play(bool loop = false);
	
	// Immediately stop audio clip from playing.
	void Stop(AudioClip audio_clip);
	// Stops all audio clips.
	void Stop();

	// Volume is a value from 0 to 100.
	void SetVolume(AudioClip audio_clip, float volume);
	// Sets volume for all audio clips. Volume is a value from 0 to 100.
	void SetVolume(float volume);

	// Sets speed to the audio clip.
	void SetFrequency(AudioClip audio_clip, int frequency);
	// Sets speed to all audio clips.
	void SetFrequency(int frequency);

	// Pan is a value from -100 to 100 (left to right).
	void SetPan(AudioClip audio_clip, float pan);
	// Sets pan to all audio clips. Pan is a value from -100 to 100 (left to right).
	void SetPan(float pan);

private:
	std::unordered_map<AudioClip, SoundIndex> audio_clips;
};


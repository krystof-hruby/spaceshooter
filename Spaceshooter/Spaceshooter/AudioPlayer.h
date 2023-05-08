// AudioPlayer.h
// Krystof Hruby
// 2023

#pragma once

#include "mysoundengine.h"

// String with L prefix. Path to audio clip location.
typedef const wchar_t* AudioClip;

// Plays audio.
class AudioPlayer {
public:
	// Returns singleton instance.
	static AudioPlayer& GetInstance();

	// Loads and plays provided audio clip.
	// Returns the sound index of the audio clip.
	SoundIndex PlayAudioClip(AudioClip audio_clip, float volume = 100, bool loop = false) const;

	// Stops audio clip with this index.
	void StopAudioClip(SoundIndex index);

	// Stops playing all audio clips.
	void StopAllAudioClips() const;

private:
	// Singleton
	AudioPlayer() { }
	AudioPlayer(AudioPlayer const& copy) = delete;
	AudioPlayer operator = (AudioPlayer const& copy) = delete;
};


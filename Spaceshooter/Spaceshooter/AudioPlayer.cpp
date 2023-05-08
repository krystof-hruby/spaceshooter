// AudioPlayer.cpp
// Krystof Hruby
// 2023

#include "AudioPlayer.h"

AudioPlayer& AudioPlayer::GetInstance() {
	static AudioPlayer instance;
	return instance;
}

SoundIndex AudioPlayer::PlayAudioClip(AudioClip audio_clip, float volume, bool loop) const {
	SoundIndex sound = MySoundEngine::GetInstance()->LoadWav(audio_clip);
	
	// MySoundEngine volume goes from -10000 to 0
	MySoundEngine::GetInstance()->SetVolume(sound, (int)((volume * 100) - 10000));

	MySoundEngine::GetInstance()->Play(sound, loop);

	return sound;
}

void AudioPlayer::StopAudioClip(SoundIndex index) {
	MySoundEngine::GetInstance()->Stop(index);
}

void AudioPlayer::StopAllAudioClips() const {
	MySoundEngine::GetInstance()->StopAllSounds();
}

// Component_SoundEmitter.cpp
// Krystof Hruby
// 2023

#include "Component_AudioEmitter.h"

void Component_AudioEmitter::Load(AudioClip audio_clip) {
	this->audio_clips[audio_clip] = MySoundEngine::GetInstance()->LoadWav(audio_clip);
}

void Component_AudioEmitter::Load(std::vector<AudioClip> audio_clip) {
	for (auto sound : audio_clip)
		this->Load(sound);
}

void Component_AudioEmitter::Play(AudioClip audio_clip, bool loop) {
	// Load sound if not loaded.
	if (this->audio_clips.find(audio_clip) == this->audio_clips.end())
		this->Load(audio_clip);

	MySoundEngine::GetInstance()->Play(this->audio_clips[audio_clip], loop);
}

void Component_AudioEmitter::Play(bool loop) {
	for (auto audio_clip : this->audio_clips)
		this->Play(audio_clip.first, loop);
}

void Component_AudioEmitter::Stop(AudioClip audio_clip) {
	// Do not stop sound if not loaded.
	if (this->audio_clips.find(audio_clip) == this->audio_clips.end())
		return;
	
	MySoundEngine::GetInstance()->Stop(this->audio_clips[audio_clip]);
}

void Component_AudioEmitter::Stop() {
	for (auto audio_clip : this->audio_clips)
		this->Stop(audio_clip.first);
}

void Component_AudioEmitter::SetVolume(AudioClip audio_clip, float volume) {
	// MySoundEngine volume goes from -10000 to 0
	MySoundEngine::GetInstance()->SetVolume(this->audio_clips[audio_clip], int((volume * 100) - 10000));
}

void Component_AudioEmitter::SetVolume(float volume) {
	for (auto audio_clip : this->audio_clips)
		this->SetVolume(audio_clip.first, volume);
}

void Component_AudioEmitter::SetFrequency(AudioClip audio_clip, int frequency) {
	MySoundEngine::GetInstance()->SetFrequency(this->audio_clips[audio_clip], frequency);
}

void Component_AudioEmitter::SetFrequency(int frequency) {
	for (auto audio_clip : this->audio_clips)
		this->SetFrequency(audio_clip.first, frequency);
}

void Component_AudioEmitter::SetPan(AudioClip audio_clip, float pan) {
	// MySoundEngine pan goes from -10000 to 10000
	MySoundEngine::GetInstance()->SetPan(this->audio_clips[audio_clip], int(pan * 100));
}

void Component_AudioEmitter::SetPan(float pan) {
	for (auto audio_clip : this->audio_clips)
		this->SetPan(audio_clip.first, pan);
}
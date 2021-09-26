#ifndef BACKEND_MIXER_AUDIO_H
#define BACKEND_MIXER_AUDIO_H

// setup
int InitAudioMixer();
void CloseAudioMixer();

// sound effects
int LoadSoundEffectMixer(const char* filename, int* index);
void PlaySoundEffectMixer(int index);

// music
int PlayMusicMixer(const char* filename);
int IsMusicPlayingMixer();
void PauseMusicMixer();
void ResumeMusicMixer();
void CloseMusicMixer();

#endif

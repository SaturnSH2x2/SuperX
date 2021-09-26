#ifndef BACKEND_DUMMY_AUDIO
#define BACKEND_DUMMY_AUDIO

// setup
int  InitAudioDummy();
void CloseAudioDummy();

// sound effects
int  LoadSoundEffectDummy(const char* filename, int* index);
void PlaySoundEffectDummy(int index);

// music
int  PlayMusicDummy(const char* filename);
void MusicControlDummy();

#endif

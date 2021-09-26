#include "../SuperX.h"

// setup
int  InitAudioDummy() {
	return 1;
}

void CloseAudioDummy() { }

// sound effects
int  LoadSoundEffectDummy(const char* filename, int* index) {
	return 1;
}

void PlaySoundEffectDummy(int index) { }

// music
int  PlayMusicDummy(const char* filename) {
	return 1;
}

void MusicControlDummy() { }



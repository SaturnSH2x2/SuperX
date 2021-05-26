#include "SuperX.h"

u8 audioEnabled;
Mix_Music* musicTrack;

int InitAudio() {
	if (Mix_OpenAudio(SAMPLE_RATE, AUDIO_FORMAT, 2, CHUNK_SIZE) < 0) {
		PrintLog("ERROR: Failed to initialize audio, %s\n", SDL_GetError());
		audioEnabled = 0;
		return 1;
	}

	// one channel for music, one for sound effects
	if (Mix_AllocateChannels(2) < 0) {
		PrintLog("ERROR: Failed to allocate channels, %s\n", SDL_GetError());
		Mix_CloseAudio();
		audioEnabled = 0;
		return 1;
	}

	audioEnabled = 1;
	return 0;
}

void CloseAudio() {
	if (musicTrack) {
		Mix_FreeMusic(musicTrack);
	}

	Mix_CloseAudio();
}

int PlayMusic(const char* filename) {
	musicTrack = Mix_LoadMUS(filename);
	if (!musicTrack) 
		return 1;

	if (Mix_PlayMusic(musicTrack, -1) == -1) {
		Mix_FreeMusic(musicTrack);
		return 1;
	}

	return 0;
}

void CloseMusic() {
	Mix_FreeMusic(musicTrack);
}


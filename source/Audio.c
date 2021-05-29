#include "SuperX.h"

u8 audioEnabled;
u8 musicPlaying;

Mix_Music* musicTrack;
Mix_Chunk* soundEffects[MAX_SOUNDEFFECT];

int InitAudio() {
	if (Mix_OpenAudio(SAMPLE_RATE, AUDIO_FORMAT, 2, CHUNK_SIZE) < 0) {
		PrintLog("ERROR: Failed to initialize audio, %s\n", SDL_GetError());
		audioEnabled = 0;
		return 1;
	}

	if (Mix_AllocateChannels(MAX_CHANNELS) < 0) {
		PrintLog("ERROR: Failed to allocate channels, %s\n", SDL_GetError());
		Mix_CloseAudio();
		audioEnabled = 0;
		return 1;
	}

	for (int i = 0; i < MAX_SOUNDEFFECT; i++) {
		soundEffects[i] = NULL;
	}

	audioEnabled = 1;
	musicPlaying = 0;
	return 0;
}

void CloseAudio() {
	if (musicTrack) {
		Mix_FreeMusic(musicTrack);
	}

	Mix_CloseAudio();
}

// sound effect stuff
int LoadSoundEffect(const char* filename, int* index) {
	*index = -1;
	for (int i = 0; i < MAX_SOUNDEFFECT; i++) {
		if (!soundEffects[i]) {
			*index = i;
			break;
		}
	}

	if (*index == -1)
		return -1;

	soundEffects[*index] = Mix_LoadWAV(filename);
	if (!soundEffects[*index]) {
		PrintLog("ERROR: could not load %s as sound effect, %s\n", filename, Mix_GetError());
		return -1;
	}

	return 0;
}

void PlaySoundEffect(int index) {
	if (!soundEffects[index]) {
		PrintLog("NOTE: no sound effect loaded into index %d, ignoring.\n");
		return;
	}

	// cycle through all channels and play on the first free one it finds
	for (int i = 0; i < MAX_CHANNELS; i++) {
		if (Mix_PlayChannel(0, soundEffects[index], 0) != -1)
			break;
	}
}

// music stuff
int PlayMusic(const char* filename) {
	musicTrack = Mix_LoadMUS(filename);
	if (!musicTrack) 
		return 1;

	if (Mix_PlayMusic(musicTrack, -1) == -1) {
		Mix_FreeMusic(musicTrack);
		return 1;
	}

	musicPlaying = 1;
	return 0;
}

int IsMusicPlaying() {
	return (int) musicPlaying;
}

void PauseMusic() {
	if (musicPlaying && musicTrack) {
		Mix_PauseMusic();
		musicPlaying = 0;
	}
}

void ResumeMusic() {
	if (!musicPlaying && musicTrack) {
		Mix_ResumeMusic();
		musicPlaying = 1;
	}
}

void CloseMusic() {
	Mix_FreeMusic(musicTrack);
}


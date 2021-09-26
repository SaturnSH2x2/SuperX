#include "../SuperX.h"

// --- --- START FUNCTION POINTERS --- ---
int  (*InitAudio)();
void (*CloseAudio)();

int  (*LoadSoundEffect)(const char*, int*);
void (*PlaySoundEffect)(int);

int  (*PlayMusic)(const char*);
int  (*IsMusicPlaying)();
void (*PauseMusic)();
void (*ResumeMusic)();
void (*CloseMusic)();

// --- --- END FUNCTION POINTERS --- ---

SuperXAudioType audioType;
u8 audioEnabled;

int SetAudioBackend(SuperXAudioType aType) {
	switch (aType) {
		case SUPERX_MIXER_AUDIO:
			InitAudio  = InitAudioMixer;
			CloseAudio = CloseAudioMixer;

			LoadSoundEffect = LoadSoundEffectMixer;
			PlaySoundEffect = PlaySoundEffectMixer;

			PlayMusic      = PlayMusicMixer;
			IsMusicPlaying = IsMusicPlayingMixer;
			PauseMusic     = PauseMusicMixer;
			ResumeMusic    = ResumeMusicMixer;
			CloseMusic     = CloseMusicMixer;

			audioType = aType;
			break;
		default:
			InitAudio  = InitAudioDummy;
			CloseAudio = CloseAudioDummy;

			LoadSoundEffect = LoadSoundEffectDummy;
			PlaySoundEffect = PlaySoundEffectDummy;
			PlayMusic       = PlayMusicDummy;

			IsMusicPlaying = InitAudioDummy;
			PauseMusic     = MusicControlDummy;
			ResumeMusic    = MusicControlDummy;
			CloseMusic     = MusicControlDummy;

			audioType = SUPERX_DUMMY_AUDIO;
			break;
	};

	if (InitAudio()) {
		audioEnabled = 0;
		return 1;
	}

	return 0;
}

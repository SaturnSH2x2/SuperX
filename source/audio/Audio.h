#ifndef AUDIO_H
#define AUDIO_H

#define SAMPLE_RATE     (44100)
#define AUDIO_FORMAT    (AUDIO_S16SYS)
#define CHUNK_SIZE      (512)

#define MAX_SOUNDEFFECT (16)
#define MAX_CHANNELS    (3)

// hopefully I only have to deal with the Mixer backend,
// but I'm doing this anyway to be consistent with the
// backend model for both video and input
typedef enum {
	SUPERX_MIXER_AUDIO,
	SUPERX_DUMMY_AUDIO
} SuperXAudioType;

extern SuperXAudioType audioType;

extern u8 audioEnabled;

// --- --- START FUNCTION POINTERS --- ---

// setup
extern int  (*InitAudio)();
extern void (*CloseAudio)();

// sound effects
extern int  (*LoadSoundEffect)(const char*, int*);
extern void (*PlaySoundEffect)(int);

// music
extern int  (*PlayMusic)(const char*);
extern int  (*IsMusicPlaying)();
extern void (*PauseMusic)();
extern void (*ResumeMusic)();
extern void (*CloseMusic)();

// --- --- END FUNCTION POINTERS --- ---

int SetAudioBackend(SuperXAudioType aType);

#endif

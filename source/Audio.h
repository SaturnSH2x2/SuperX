#ifndef AUDIO_H
#define AUDIO_H

#define SAMPLE_RATE     (44100)
#define AUDIO_FORMAT    (AUDIO_S16SYS)
#define CHUNK_SIZE      (512)

#define MAX_SOUNDEFFECT (16)
#define MAX_CHANNELS    (3)

extern u8 audioEnabled;

int InitAudio();
void CloseAudio();

// sound effects
int LoadSoundEffect(const char* filename, int* index);
void PlaySoundEffect(int index);

// music
int PlayMusic(const char* filename);
int IsMusicPlaying();
void PauseMusic();
void ResumeMusic();
void CloseMusic();

#endif

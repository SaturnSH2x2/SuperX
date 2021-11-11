/*
 *	Generally speaking, SuperX uses SDL 2.0 for video, input, and audio. There are
 *	some platform-specific exceptions, though.
 *
 *	The 3DS only has (current) support for SDL 1.2, but that should only be used for audio,
 *	as the system will use its own custom render backend.
 * */

#define SUPERX_PC    (0)
#define SUPERX_3DS   (1)
#define SUPERX_NX    (2)
#define SUPERX_DC    (3)

#ifndef COMMIT
#define COMMIT "unknown"
#endif

#if defined __3DS__
#define SUPERX_PLATFORM SUPERX_3DS
#define SUPERX_USING_SDL2      (0)
#define SUPERX_USING_SDL_RWOPS (0)
#define SUPERX_USING_SDLMIXER  (1)
#elif defined _DC
#define SUPERX_PLATFORM SUPERX_DC
#define SUPERX_USING_SDL2      (0)
#define SUPERX_USING_SDL_RWOPS (0)
#define SUPERX_USING_SDLMIXER  (0)
#else
#define SUPERX_PLATFORM SUPERX_PC
#define SUPERX_USING_SDL2      (1)
#define SUPERX_USING_SDL_RWOPS (1)
#define SUPERX_USING_SDLMIXER  (1)
#endif

#if SUPERX_PLATFORM != SUPERX_3DS
// --- preprocessor variables and such ---
#define Uint8  u8
#define Uint16 u16
#define Uint32 u32
#define Uint64 u64
#endif

#define Sint8  s8
#define Sint16 s16
#define Sint32 s32
#define Sint64 s64

// --- include statements ---
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lodepng.h>
#include <jansson.h>
#include <gifdec.h>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <luaxlib.h>
}

#if SUPERX_PLATFORM == SUPERX_PC
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

/*
	TODO: just a general laundry list of stuff to implement
		*  Properly load in objects from object layers.
		*  Load tilemask collision data from JSON (generating said data should be done outside the engine)
		*  Rework palette loading from GIFs
		*  Add sprite animation support. Somehow. Maybe implement a way to
			play GIF animations directly?

	Actually implementing 2D Sonic physics comes later (and shouldn't be hard-coded
	into the engine)
*/

#include "Math.h"
#include "String.h"
#include "File.h"
#include "Debug.h"
#include "render/Render.h"
#include "render/Palette.h"
#include "render/Sprite.h"
#include "Script.h"
#include "Config.h"
#include "input/Input.h"
#include "audio/Audio.h"
#include "Scene.h"

#include "audio/backend_mixer_audio.h"
#include "audio/backend_dummy_audio.h"
#include "render/backend_sw.h"
#include "render/backend_dummy_render.h"
#include "input/backend_gc.h"
#include "input/backend_dummy_input.h"

// --- engine variables ---
typedef enum {
	SUPERX_MAINGAME,
	SUPERX_DEVMENU,
	SUPERX_SCRIPTERROR,
	SUPERX_PAUSED,
	SUPERX_EXIT
} SuperXState;

extern SuperXState engineState;
extern int windowSizeX, windowSizeY;
extern char isFullscreen;
extern char displayPaletteOverlay;
extern char basePath[255];
extern int frameRate;

#if SUPERX_USING_SDL2
int SetupSDL(u32 windowFlags);
void CloseSDL();
#endif

void ToggleFullscreen();

int InitSuperX();
void RunSuperX();
void CloseSuperX();

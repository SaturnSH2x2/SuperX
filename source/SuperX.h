// --- preprocessor variables and such ---
#define Uint8  u8
#define Uint16 u16
#define Uint32 u32
#define Uint64 u64

#define Sint8  s8
#define Sint16 s16
#define Sint32 s32
#define Sint64 s64

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

#if defined _3DS
#define SUPERX_PLATFORM SUPERX_3DS
#define SUPERX_USING_SDL2 (0)
#define SUPERX_USING_SDL1 (0)
#elif defined _DC
#define SUPERX_PLATFORM SUPERX_DC
#define SUPERX_USING_SDL2 (1)
#define SUPERX_USING_SDL1 (0)
#else
#define SUPERX_PLATFORM SUPERX_PC
#define SUPERX_USING_SDL2 (1)
#define SUPERX_USING_SDL1 (0)
#endif

// --- include statements ---
#include <stdio.h>
#include <stdlib.h>
#include <lodepng.h>
#include <jansson.h>

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
		1. Scene loading from .tmx files (should be top priority)
		2. Add keyboard input support (some people don't have controllers)
		3. Add sprite animation support. Somehow. Maybe implement a way to
			play GIF animations directly?
		4. Implement color palettes, as well as automatic detection of color
		   palettes (so that indexed images aren't strictly necessary)

	Actually implementing 2D Sonic physics comes later (and shouldn't be hard-coded
	into the engine)
*/

#include "String.h"
#include "File.h"
#include "Debug.h"
#include "Render.h"
#include "Sprite.h"
#include "Script.h"
#include "Userdata.h"
#include "Input.h"
#include "Audio.h"

// --- engine variables ---
typedef enum {
	SUPERX_MAINGAME,
	SUPERX_DEVMENU,
	SUPERX_SCRIPTERROR,
	SUPERX_PAUSED,
	SUPERX_EXIT
} SuperXState;

typedef enum {
	SUPERX_SW_RENDER,
	SUPERX_C2D_RENDER,
	SUPERX_KOS_RENDER
} SuperXRenderType;

extern SuperXState engineState;
extern SuperXRenderType renderType;
extern int windowSizeX, windowSizeY;
extern char isFullscreen;
extern char basePath[255];
extern int frameRate;

// --- SDL functions ---
int SetupSDL(u32 windowFlags);
void ProcessEventsSDL();
void CloseSDL();

int InitSuperX();
void RunSuperX();
void CloseSuperX();

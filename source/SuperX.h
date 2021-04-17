// --- preprocessor variables and such ---
#define Uint8  u8
#define Uint16 u16
#define Uint32 u32
#define Uint64 u64

#define Sint8  s8
#define Sint16 s16
#define Sint32 s32
#define Sint64 s64

// each component of SDL 1.2 can be enabled separately
#define SDL1_USE_TIMER (1)
#define SDL1_USE_AUDIO (1)
#define SDL1_USE_VIDEO (1)
#define SDL1_USE_INPUT (1)

#define USING_SDL1 (SDL1_USE_TIMER || SDL1_USE_AUDIO || SDL1_USE_VIDEO || SDL1_USE_INPUT)

// --- include statements ---
#include <stdio.h>
#include <stdlib.h>
#include <lodepng.h>

extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <luaxlib.h>
}

#if USING_SDL1
#include <SDL/SDL.h>
#endif

/*
	TODO: main priorities right now should be
		1. Implement Lua scripting support (so you don't have to 
			hard-code tests into the engine)
		2. Add tileset support (worry about parallax later)
		3. Add sprite animation support. Somehow. Maybe implement a way to
			play GIF animations directly?

	Actually implementing 2D Sonic physics comes later.
*/

#include "String.h"
#include "File.h"
#include "Debug.h"
#include "Render.h"
#include "Sprite.h"
#include "Script.h"

// --- engine variables ---
typedef enum {
	SUPERX_MAINGAME,
	SUPERX_DEVMENU,
	SUPERX_PAUSED,
	SUPERX_EXIT
} SuperXState;

typedef enum {
	SUPERX_SW_RENDER,
	SUPERX_HW_RENDER
} SuperXRenderType;

extern SuperXState engineState;
extern SuperXRenderType renderType;
extern char basePath[255];
extern int frameRate;

// --- SDL functions ---
int SetupSDL();
void ProcessEventsSDL();
void CloseSDL();

int InitSuperX();
void RunSuperX();
void CloseSuperX();

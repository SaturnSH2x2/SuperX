#include "SuperX.h"

SuperXState engineState;
SuperXRenderType renderType;

char isFullscreen;
char basePath[255];

int frameRate;

// --- SDL-dependent functions ---
int SetupSDL(int x, int y) {
#if SDL1_USE_AUDIO
	if (SDL_Init(SDL_INIT_AUDIO))
		return 1;
#endif

#if SDL1_USE_VIDEO
	if (SDL_Init(SDL_INIT_VIDEO))
		return 1;

	gameWindow = SDL_SetVideoMode(x, y, 16, SDL_SWSURFACE);
	if (!gameWindow)
		return 1;

	screenBuffer = SDL_CreateRGBSurface(SDL_SWSURFACE, x, y, 16, 0, 0, 0, 0);
	if (!screenBuffer)
		return 1;
#endif

#if SDL1_USE_TIMER
	if (SDL_Init(SDL_INIT_TIMER))
		return 1;
#endif

#if SDL1_USE_INPUT
	if (SDL_Init(SDL_INIT_JOYSTICK))
		return 1;
#endif

	return 0;
}

void ToggleFullscreen() {

}

void ProcessEventsSDL() {
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		switch(ev.type) {
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym) {
					case SDLK_F12:
						if (engineState == SUPERX_PAUSED)
							engineState = SUPERX_MAINGAME;
						else
							engineState = SUPERX_PAUSED;
						break;
					default:
						break;
				}
				break;
			case SDL_QUIT:
				engineState = SUPERX_EXIT;
				break;
			default:
				break;
		}
	}
}

void CloseSDL() {
	SDL_FreeSurface(gameWindow);
	SDL_Quit();
}

// --- main engine functions ---
int InitSuperX() {
	memset(basePath, 0, sizeof(basePath));

	// TODO: fb resolution is currently hard-coded,
	// implement code to load from config file later
	if (CreateFrameBuffer(424, 240)) {
		PrintLog("ERROR: failed to allocate frameBuffer\n");
		return 1;
	}

	// TODO: resolution is also hard-coded, same as above
	if (SetupSDL(1280, 720)) {
		PrintLog("ERROR: failed to initialize SDL\n");
		return 1;
	}

	engineState = SUPERX_MAINGAME;
	renderType  = SUPERX_SW_RENDER;
	frameRate   = 60;

	isFullscreen = 0;

	/* testing code begins here */
	PrintLog("Resolution: %dx%d\n", screenBuffer->w, screenBuffer->h);
	InitObject("debug.lua");
	/* end testing code */

	return 0;
}

void CloseSuperX() {
	ReleaseFrameBuffer();
	CloseSDL();
}

void RunSuperX() {
	int start, end;

	while (engineState != SUPERX_EXIT) {
		// script stuff
		if (engineState == SUPERX_MAINGAME) {
			UpdateObjects();
		}

#if SDL1_USE_TIMER
		start = SDL_GetTicks();
#endif

#if SDL1_USE_INPUT
		ProcessEventsSDL();
#endif

#if SDL1_USE_VIDEO
		UpdateScreenSDL();
#endif

#if SDL1_USE_TIMER
		end = SDL_GetTicks();
		if (end - start < 1000.0f / frameRate) {
			SDL_Delay( (1000.0f / frameRate) - (end - start) );
		}
#endif
	}

	PrintLog("exiting engine...\n");
}

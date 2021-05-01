#include "SuperX.h"

SuperXState engineState;
SuperXRenderType renderType;

char isFullscreen;
char basePath[255];

int frameRate;

// --- SDL-dependent functions ---
int SetupSDL(int x, int y, u32 windowFlags) {
#if SUPERX_USING_SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		PrintLog("ERROR: Could not initialize SDL\n");
		return 1;
	}

	SDL_CreateWindowAndRenderer(x, y, windowFlags, &gameWindow, &renderer);

	if (!gameWindow || !renderer) {
		PrintLog("ERROR: Could not create window\n");
		return 1;
	}

	PrintLog("Creating window of resolution %dx%d\n", x, y);
#endif

	return 0;
}

void ToggleFullscreen() {
	if (isFullscreen)
		SDL_SetWindowFullscreen(gameWindow, 0);
	else
		SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

	isFullscreen = !isFullscreen;
}

void ProcessEventsSDL() {
	SDL_Event ev;

	while (SDL_PollEvent(&ev)) {
		switch(ev.type) {
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym) {
					case SDLK_F4:
						ToggleFullscreen();
						break;
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
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(bufferTexture);
	SDL_Quit();

	PrintLog("Exiting SuperX...\n");
}

// --- main engine functions ---
int InitSuperX() {
	memset(basePath, 0, sizeof(basePath));

	// TODO: resolution is also hard-coded, same as above
	if (SetupSDL(1280, 720, 0)) {
		PrintLog("ERROR: failed to initialize SDL\n");
		return 1;
	}

	// TODO: fb resolution is currently hard-coded,
	// implement code to load from config file later
	if (CreateFrameBuffer(424, 240)) {
		PrintLog("ERROR: failed to allocate frameBuffer\n");
		return 1;
	}

	engineState = SUPERX_MAINGAME;
	renderType  = SUPERX_SW_RENDER;
	frameRate   = 60;

	isFullscreen = 0;

	// TODO: load a full scene instead of just an object
	InitObject("debug.lua");

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

		start = SDL_GetTicks();
		ProcessEventsSDL();

		if (engineState == SUPERX_MAINGAME)
			UpdateScreenSDL();

		end = SDL_GetTicks();
		if (end - start < 1000.0f / frameRate) {
			SDL_Delay( (1000.0f / frameRate) - (end - start) );
		}
	}
}

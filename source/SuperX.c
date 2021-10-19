#include "SuperX.h"

SuperXState engineState;
int windowSizeX = DEFAULT_SCREENSIZEX;
int windowSizeY = DEFAULT_SCREENSIZEY;

char isFullscreen = 0;
char displayPaletteOverlay = 0;
char basePath[255];

int frameRate;

#if SUPERX_USING_SDL2
int SetupSDL(u32 windowFlags) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		PrintLog("ERROR: Could not initialize SDL\n");
		return 1;
	}

	if (renderType == SUPERX_SW_RENDER) { 
		SDL_CreateWindowAndRenderer(windowSizeX, windowSizeY, windowFlags, &gameWindow, &renderer);

		if (!gameWindow || !renderer) {
			PrintLog("ERROR: Could not create window\n");
			return 1;
		}

		PrintLog("Creating window of resolution %dx%d\n", windowSizeX, windowSizeY);
	}

	return 0;
}
#endif

void ToggleFullscreen() {
#if SUPERX_USING_SDL2
	if (isFullscreen)
		SDL_SetWindowFullscreen(gameWindow, 0);
	else
		SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

	isFullscreen = !isFullscreen;
#endif
}

/*
void ProcessEvents() {
	UpdateController();
}
*/

#if SUPERX_USING_SDL2
void CloseSDL() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(bufferTexture);

	SDL_Quit();

	PrintLog("Exiting SuperX...\n");
}
#endif

// --- main engine functions ---
int InitSuperX() {
	memset(basePath, 0, sizeof(basePath));
	renderType  = SUPERX_SW_RENDER;
	frameRate   = 60;

	// TODO: currently hard-coded, do something about this
	useDataFolder = 1;

	if (LoadGameConfig()) {
		PrintLog("ERROR: while loading GameConfig.json\n");
		return 1;
	}

	if (LoadUserConfig()) {
		PrintLog("ERROR: while loading config.json\n");
		return 1;
	}

#if SUPERX_USING_SDL2
	if (SetupSDL(0)) {
		PrintLog("ERROR: failed to initialize SDL\n");
		return 1;
	}
#endif

#if SUPERX_USING_SDL2
	if (isFullscreen) {
		SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
#endif

	engineState = SUPERX_MAINGAME;

	if (SetRenderBackend(SUPERX_SW_RENDER)) {
		PrintLog("ERROR: could not initialize render backend\n");
		return 1;
	}

	if (SetInputBackend(SUPERX_GAMECONTROLLER_INPUT)) {
		PrintLog("ERROR: could not initialize input backend\n");
		return 1;
	}

	if (SetAudioBackend(SUPERX_MIXER_AUDIO)) {
		PrintLog("ERROR: could not initialize audio backend, audio is disabled\n");
	}


	if (InitPalettes()) {
		PrintLog("ERROR: could not allocate memory for color palettes\n");
		return 1;
	}

	LoadScene("./green-hill-map.json");

	// TODO: load a full scene instead of just an object
	InitObject("debug.lua", 1, 0.0, 0.0);

	return 0;
}

void CloseSuperX() {
	RenderBackendExit();
	CloseGameConfig();
	CloseAudio();

#if SUPERX_USING_SDL2
	CloseSDL();
#endif
}

void RunSuperX() {
	while (engineState != SUPERX_EXIT) {
		FrameLimitStart();

		// get input before running scripts
		UpdateController();

		switch (engineState) {
			case SUPERX_MAINGAME:
				// TODO: allow sprite/layer draw order to be set by the user
				DrawLayer(0);
				UpdateObjects(1);
				break;
			case SUPERX_DEVMENU:
				RunDevMenu();
				break;
			default:
				break;
		};


		if (displayPaletteOverlay) {
			DisplayPaletteOverlay();
		}

		RenderBackendUpdate();

		FrameLimitEnd();
	}
}

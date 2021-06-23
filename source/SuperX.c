#include "SuperX.h"

SuperXState engineState;
SuperXRenderType renderType;

int windowSizeX = DEFAULT_SCREENSIZEX;
int windowSizeY = DEFAULT_SCREENSIZEY;

char isFullscreen = 0;
char basePath[255];

int frameRate;

// --- SDL-dependent functions ---
int SetupSDL(u32 windowFlags) {
#if SUPERX_USING_SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		PrintLog("ERROR: Could not initialize SDL\n");
		return 1;
	}

	SDL_CreateWindowAndRenderer(windowSizeX, windowSizeY, windowFlags, &gameWindow, &renderer);

	if (!gameWindow || !renderer) {
		PrintLog("ERROR: Could not create window\n");
		return 1;
	}

	PrintLog("Creating window of resolution %dx%d\n", windowSizeX, windowSizeY);
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
			case SDL_CONTROLLERDEVICEADDED:
				HandleControllerConnect(&ev);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				HandleControllerDisconnect(&ev);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				UpdateController(ev.cbutton.which, ev.cbutton.button, 1);
				break;
			case SDL_CONTROLLERBUTTONUP:
				UpdateController(ev.cbutton.which, ev.cbutton.button, 0);
				break;
			case SDL_KEYDOWN:
				switch(ev.key.keysym.sym) {
					case SDLK_UP:
						if (engineState == SUPERX_DEVMENU)
							DevMenuInput(DEVINPUT_UP);
						break;
					case SDLK_DOWN:
						if (engineState == SUPERX_DEVMENU)
							DevMenuInput(DEVINPUT_DOWN);
						break;
					case SDLK_RETURN:
						if (engineState == SUPERX_DEVMENU)
							DevMenuInput(DEVINPUT_SELECT);
						break;
					case SDLK_ESCAPE:
						if (engineState == SUPERX_DEVMENU ||
						    engineState == SUPERX_SCRIPTERROR) {
							ResumeMusic();
							engineState = SUPERX_MAINGAME;
						} else {
							InitDevMenu();
							engineState = SUPERX_DEVMENU;
						}
						break;
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

	if (SetupSDL(0)) {
		PrintLog("ERROR: failed to initialize SDL\n");
		return 1;
	}

	if (InitControllerInput()) {
		PrintLog("ERROR: could not initialize controller input\n");
		return 1;
	}

	if (InitAudio()) {
		PrintLog("NOTE: audio playback disabled\n");
	}

	if (isFullscreen) {
		SDL_SetWindowFullscreen(gameWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

	if (CreateFrameBuffer()) {
		PrintLog("ERROR: failed to allocate frameBuffer\n");
		return 1;
	}

	engineState = SUPERX_MAINGAME;
	renderType  = SUPERX_SW_RENDER;
	frameRate   = 60;

	// TODO: load a full scene instead of just an object
	InitObject("debug.lua", 0);

	return 0;
}

void CloseSuperX() {
	ReleaseFrameBuffer();
	CloseGameConfig();
	CloseAudio();
	CloseSDL();
}

void RunSuperX() {
	int start, end;

	while (engineState != SUPERX_EXIT) {
		// reset keydown/keyup
		memset(down, 0, MAX_GAMEPADS * 12);
		memset(up,   0, MAX_GAMEPADS * 12);

		start = SDL_GetTicks();

		// get input before running scripts
		ProcessEventsSDL();

		switch (engineState) {
			case SUPERX_MAINGAME:
				UpdateObjects(0);
				break;
			case SUPERX_DEVMENU:
				RunDevMenu();
				break;
			default:
				break;
		};

		UpdateScreenSDL();

		end = SDL_GetTicks();
		if (end - start < 1000.0f / frameRate) {
			SDL_Delay( (1000.0f / frameRate) - (end - start) );
		}
	}
}

#include "../SuperX.h"

#if SUPERX_USING_SDL2
int controllersConnected;
SDL_GameController* gamePads[MAX_GAMEPADS];
int gamePadWhich [MAX_GAMEPADS];

char down[MAX_GAMEPADS][12];
char held[MAX_GAMEPADS][12];
char   up[MAX_GAMEPADS][12];

int InitControllerInputGC() {
	// TODO: add option for this in config file
	swapConfirmationButton = false;

	SDL_Init(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < MAX_GAMEPADS; i++) {
		gamePads[i] = NULL;
		gamePadWhich[i] = -1;
	}

	// load mappings from file
	if (SDL_GameControllerAddMappingsFromFile("./gamecontrollerdb.txt") == -1) {
		PrintLog("ERROR: could not read game controller mappings from file, %d\n", SDL_GetError());
		return 1;
	}

	controllersConnected = 0;	
	SDL_GameControllerEventState(SDL_ENABLE);

	return 0;
}

void SDLInputGC() {
	// reset keydown/keyup
	memset(down, 0, MAX_GAMEPADS * 12);
	memset(up,   0, MAX_GAMEPADS * 12);

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
				UpdateControllerGC(ev.cbutton.which, ev.cbutton.button, 1);
				break;
			case SDL_CONTROLLERBUTTONUP:
				UpdateControllerGC(ev.cbutton.which, ev.cbutton.button, 0);
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

void UpdateControllerGC(int which, int button, int state) {
	int w;
	int b;
#if SUPERX_USING_SDL2
	w = -1;
	for (int i = 0; i < MAX_GAMEPADS; i++) {
		if (gamePadWhich[i] == which) {
			w = i;
			break;
		}
	}

	switch (button) {
		case SDL_CONTROLLER_BUTTON_A:
	 		b = BUTTON_A;
			break;
		case SDL_CONTROLLER_BUTTON_B:
			b = BUTTON_B;
			break;
		case SDL_CONTROLLER_BUTTON_X:
			b = BUTTON_X;
			break;	
		case SDL_CONTROLLER_BUTTON_Y:
			b = BUTTON_Y;
			break;
		case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
			b = BUTTON_L;
			break;
		case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
			b = BUTTON_R;
			break;
		case SDL_CONTROLLER_BUTTON_START:
			b = BUTTON_START;
			break;
		case SDL_CONTROLLER_BUTTON_BACK:
			b = BUTTON_SELECT;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_UP:
			b = BUTTON_UP;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
			b = BUTTON_DOWN;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
			b = BUTTON_LEFT;
			break;
		case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
			b = BUTTON_RIGHT;
			break;
		default:
			b = -1;
			break;
	}
#endif

	if (b == -1 || w == -1)
		return;

	held[w][b] = state;
	if (state) 
		down[w][b] = 1;
	else
		up[w][b] = 1;
}

int GetButtonDownGC(int port, int button) {
	return down[port][button];
}

int GetButtonHeldGC(int port, int button) {
	return held[port][button];
}

int GetButtonUpGC(int port, int button) {
	return up[port][button];
}
void HandleControllerConnect(SDL_Event* e) {
	if (controllersConnected < MAX_GAMEPADS) {
		// get next available controller slot
		int slot = -1;
		for (int i = 0; i < MAX_GAMEPADS; i++) {
			if (gamePadWhich[i] == e->cdevice.which) {
				PrintLog(
				  "NOTE: Connected controller has same which as existing controller (%d), ignoring\n",
				  e->cdevice.which
				  );
				return;
			}

			if (gamePads[i] == NULL) {
				slot = i;
				break;
			}
		}

		if (slot == -1) {
			PrintLog("ERROR: no available controller slots available, apparently?\n");
			return;
		}

		gamePads[slot] = SDL_GameControllerOpen(e->cdevice.which);
		if (SDL_GameControllerGetAttached(gamePads[slot]) != 1) {
			PrintLog("ERROR: %s\n", SDL_GetError());
			SDL_GameControllerClose(gamePads[slot]);
			return;
		}

		gamePadWhich[slot] = GetInstanceID(gamePads[slot]);

		PrintLog("Controller %d added: %s, which: %d, ID: %d\n", slot, SDL_GameControllerName(gamePads[e->cdevice.which]), e->cdevice.which, GetInstanceID(gamePads[slot]));
		controllersConnected++;
	} else {
		PrintLog("Controller connected, ignoring (which given: %d)\n", e->cdevice.which);
	}
}

void HandleControllerDisconnect(SDL_Event* e) {
	int slot = -1;
	for (int i = 0; i < MAX_GAMEPADS; i++) {
		if (gamePadWhich[i] == e->cdevice.which) {
			slot = i;
			break;
		}
	}

	if (slot == -1) {
		PrintLog("Controller disconnected, ignoring (which given: %d)\n", e->cdevice.which);
		return;
	}

	gamePadWhich[slot] = -1;
	gamePads[slot] = NULL;

	PrintLog("Controller %d disconnected\n", slot);
	controllersConnected--;
}	

#endif

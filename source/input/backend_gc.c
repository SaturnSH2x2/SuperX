#include "../SuperX.h"

#if SUPERX_USING_SDL2
int controllersConnected;
SDL_GameController* gamePads[MAX_GAMEPADS];
int gamePadWhich [MAX_GAMEPADS];

char down[MAX_GAMEPADS][12];
char held[MAX_GAMEPADS][12];
char   up[MAX_GAMEPADS][12];

// keyboard input always associated with port 1
KeyMap keyboardMappings[12];

const SDL_Keycode defaultMap[12] = {
	SDL_SCANCODE_UP,
	SDL_SCANCODE_DOWN,
	SDL_SCANCODE_LEFT,
	SDL_SCANCODE_RIGHT,
	SDL_SCANCODE_Z,
	SDL_SCANCODE_X,
	SDL_SCANCODE_A,
	SDL_SCANCODE_S,
	SDL_SCANCODE_Q,
	SDL_SCANCODE_W,
	SDL_SCANCODE_RETURN,
	SDL_SCANCODE_RSHIFT
};

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

int LoadKeyboardMapping(json_t* root, char* altered) {
	char createObject = 0;
	memset(keyboardMappings, 0, 12 * sizeof(KeyMap));

	json_t* input = json_object_get(root, "input");
	if (!json_is_object(input)) {
		createObject = 1;
		*altered = 1;
		input = json_object();
	}

	json_t* mapping = json_object_get(input, "keyboard-mapping");
	if (!mapping) {
		json_decref(mapping);
		mapping = json_object();

		// populate with default keyboard mappings
		for (int i = 0; i < 12; i++) {
			json_object_set(mapping, keyNames[i], json_integer(defaultMap[i])); 
		}

		json_object_set(input, "keyboard-mapping", mapping);
	} else if (!json_is_object(mapping)) {
		PrintLog("ERROR: expected object for \"keyboard-mapping\"\n");
		json_decref(mapping);
		return 1;
	}

	const char* key;
	json_t* val;
	int bIndex = 0;
	json_object_foreach(mapping, key, val) {
		for (int i = 0; i < 12; i++) {
			// ignore non-number values
			if (!json_is_number(val))
				continue;

			if (strcmp(key, keyNames[i]) == 0) {
				keyboardMappings[bIndex].key = json_integer_value(val);
				keyboardMappings[bIndex].button = i;
				bIndex++;
			}
		}
	}

	if (createObject) {
		json_object_set(root, "input", input);
	}

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

						goto read_in;
						break;
					case SDLK_DOWN:
						if (engineState == SUPERX_DEVMENU)
							DevMenuInput(DEVINPUT_DOWN);

						goto read_in;
						break;
					case SDLK_RETURN:
						if (engineState == SUPERX_DEVMENU)
							DevMenuInput(DEVINPUT_SELECT);

						goto read_in;
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
					case SDLK_F10:
						displayPaletteOverlay = !displayPaletteOverlay;
						break;
					default:
						read_in:
						UpdateKeyboard(ev.key.keysym.scancode, 1);
						break;
				}
				break;
			case SDL_KEYUP:
				UpdateKeyboard(ev.key.keysym.scancode, 0);
				break;
			case SDL_QUIT:
				engineState = SUPERX_EXIT;
				break;
			default:
				break;
		}
	}
}

void UpdateKeyboard(SDL_Keycode k, int kDown) {
	for (int i = 0; i < 12; i++) {
		if (k == keyboardMappings[i].key) {
			if (kDown) {
				down[0][keyboardMappings[i].button] = 1;
				held[0][keyboardMappings[i].button] = 1;
			} else {
			 	  up[0][keyboardMappings[i].button] = 1;
				held[0][keyboardMappings[i].button] = 0;
			}
		}
	}
}

void UpdateControllerGC(int which, int button, int state) {
	int w;
	int b;
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

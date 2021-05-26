#include "SuperX.h"

int controllersConnected;
SDL_GameController* gamePads[MAX_GAMEPADS];
int gamePadWhich [MAX_GAMEPADS];

int InitControllerInput() {
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

		PrintLog("Controller %d added: %s, which: %d\n", slot, SDL_GameControllerName(gamePads[e->cdevice.which]), e->cdevice.which);
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

void HandleControllerInput() {

}

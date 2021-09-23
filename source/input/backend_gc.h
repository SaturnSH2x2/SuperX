#ifndef BACKEND_GC_H
#define BACKEND_GC_H

#if SUPERX_USING_SDL2
inline s32 GetInstanceID(SDL_GameController* g) {
	SDL_Joystick* j = SDL_GameControllerGetJoystick(g);
	if (!j) 
		return -1;

	return SDL_JoystickInstanceID(j);
}

extern char down[MAX_GAMEPADS][12];
extern char held[MAX_GAMEPADS][12];
extern char   up[MAX_GAMEPADS][12];

extern SDL_GameController* gamePads[MAX_GAMEPADS];

int InitControllerInputGC();
int GetButtonDownGC(int port, int button);
int GetButtonHeldGC(int port, int button);
int GetButtonUpGC(int port, int button);

void HandleControllerConnect(SDL_Event* e);
void HandleControllerDisconnect(SDL_Event* e);
void SDLInputGC();
void UpdateControllerGC(int which, int button, int state);
#endif

#endif

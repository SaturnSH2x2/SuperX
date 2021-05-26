#ifndef INPUT_H
#define INPUT_H

#define MAX_GAMEPADS 4

inline s32 GetInstanceID(SDL_GameController* g) {
	SDL_Joystick* j = SDL_GameControllerGetJoystick(g);
	if (!j) 
		return -1;

	return SDL_JoystickInstanceID(j);
}

extern SDL_GameController* gamePads[MAX_GAMEPADS];

int InitControllerInput();
void HandleControllerConnect(SDL_Event* e);
void HandleControllerDisconnect(SDL_Event* e);
void HandleControllerInput();

#endif

#ifndef INPUT_H
#define INPUT_H

#define MAX_GAMEPADS 4

#define BUTTON_UP      (0)
#define BUTTON_DOWN    (1)
#define BUTTON_LEFT    (2)
#define BUTTON_RIGHT   (3)
#define BUTTON_A       (4)
#define BUTTON_B       (5)
#define BUTTON_X       (6)
#define BUTTON_Y       (7)
#define BUTTON_L       (8)
#define BUTTON_R       (9)
#define BUTTON_START  (10)
#define BUTTON_SELECT (11)

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

int InitControllerInput();
void HandleControllerConnect(SDL_Event* e);
void HandleControllerDisconnect(SDL_Event* e);
void UpdateController(int which, int button, int state);

int GetButtonDown(int port, int button);
int GetButtonHeld(int port, int button);
int GetButtonUp(int port, int button);

#endif

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

typedef enum {
	SUPERX_GAMECONTROLLER_INPUT,
	SUPERX_HID_3DS_INPUT,
	SUPERX_MAPLE_INPUT,
	SUPERX_DUMMY_INPUT
} SuperXInputType;

extern SuperXInputType inputType;
extern bool swapConfirmationButton;

extern int (*InitControllerInput)();
extern void (*UpdateController)();
extern int (*GetButtonDown)(int, int);
extern int (*GetButtonHeld)(int, int);
extern int (*GetButtonUp)(int, int);

int SetInputBackend(SuperXInputType iType);

#endif

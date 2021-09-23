#include "SuperX.h"

bool swapConfirmationButton;

SuperXInputType inputType;

int (*InitControllerInput)();
void (*UpdateController)();
int (*GetButtonDown)(int, int);
int (*GetButtonHeld)(int, int);
int (*GetButtonUp)(int, int);

int SetInputBackend(SuperXInputType iType) {
	switch (iType) {
		case SUPERX_GAMECONTROLLER_INPUT:
			InitControllerInput = InitControllerInputGC;
			UpdateController    = SDLInputGC;
			GetButtonDown       = GetButtonDownGC;
			GetButtonHeld       = GetButtonHeldGC;
			GetButtonUp         = GetButtonUpGC;

			inputType = iType;
			break;
		default:
			InitControllerInput = InitDummyInput;
			UpdateController    = UpdateDummyInput;
			GetButtonDown       = GetButtonDummy;
			GetButtonHeld       = GetButtonDummy;
			GetButtonUp         = GetButtonDummy;
			inputType = SUPERX_DUMMY_INPUT;
			break;
	}

	return InitControllerInput();
}

#include "../SuperX.h"

bool swapConfirmationButton;

SuperXInputType inputType;

int (*InitControllerInput)();
void (*UpdateController)();
int (*GetButtonDown)(int, int);
int (*GetButtonHeld)(int, int);
int (*GetButtonUp)(int, int);

int (*LoadKeyMapping)(json_t*, char*);

const char* keyNames[12] = {
	"up",
	"down",
	"left",
	"right",
	"A",
	"B",
	"X",
	"Y",
	"L",
	"R",
	"start",
	"select"
};

void SetInputBackend(SuperXInputType iType) {
	switch (iType) {
		case SUPERX_GAMECONTROLLER_INPUT:
			InitControllerInput = InitControllerInputGC;
			LoadKeyMapping      = LoadKeyboardMapping;
			UpdateController    = SDLInputGC;
			GetButtonDown       = GetButtonDownGC;
			GetButtonHeld       = GetButtonHeldGC;
			GetButtonUp         = GetButtonUpGC;

			inputType = iType;
			break;
		default:
			InitControllerInput = InitDummyInput;
			LoadKeyMapping      = DummyKeyMap;
			UpdateController    = UpdateDummyInput;
			GetButtonDown       = GetButtonDummy;
			GetButtonHeld       = GetButtonDummy;
			GetButtonUp         = GetButtonDummy;
			inputType = SUPERX_DUMMY_INPUT;
			break;
	}
}

#include "SuperX.h"

int devMenuSelect;
DevMenuState dState;

const char* devMenuOpts[4] = {
	"Resume Scene",
	"Restart Scene",
	"Scene Select",
	"Exit Game"
};

static const int width = 320;
static const int height = 175;

int devXPos, devYPos;

// heavily based on RSDKv3 decomp's logging function
void PrintLog(const char* str, ...) {
	char buf[0x100];

	// construct string
	va_list args;
	va_start(args, str);
	vsprintf(buf, str, args);
	printf("%s", buf);

	// TODO: implement this right at some point
	//char fPath[0x100];
	//CopyString(fPath, basePath, 255);
	//AppendString(fPath, "log.txt", 255);	

	FileIO* f = fOpen("log.txt", "a");
	if (f) {
		fWrite(f, &buf, GetStringLength(buf), 1);
		fClose(f);
	}
}

void InitDevMenu() {
	PauseMusic();
	dState = DEV_MAIN_MENU;

	devXPos = bufferSizeX / 2 - (width / 2);
	devYPos = bufferSizeY / 2 - (height / 2);

	if (renderType == SUPERX_SW_RENDER) {
		DrawRectangleSW(devXPos, devYPos, width, height, 0xF807);
	}

	devMenuSelect = 0;

	DrawText(devXPos + 8, devYPos + 8, 0xffff, width - 8, "WELCOME TO SUPERX DEVELOPER MENU");
	DrawText(devXPos + 8, devYPos + 17, 0xffff, width - 8, "SuperX, commit: %s", COMMIT);
}

void DevMenuInput(DevInput stat) {
	char select = 0;
	switch (stat) {
		case DEVINPUT_UP:
			devMenuSelect--;
			break;
		case DEVINPUT_DOWN:
			devMenuSelect++;
			break;
		case DEVINPUT_SELECT:
			select = 1;
			break;
		default:
			break;
	};

	if (select) {
		switch (devMenuSelect) {
			case 0:
				ResumeMusic();
				engineState = SUPERX_MAINGAME;
				break;
			// TODO: cases 1 and 2 (restarting and selecting scenes)
			case 3:
				engineState = SUPERX_EXIT;
				break;
		};
	}

	if (dState == DEV_MAIN_MENU) {
		if (devMenuSelect >= 4)
			devMenuSelect = 0;
		if (devMenuSelect < 0)
			devMenuSelect = 3;
	}
}

void RunDevMenu() {
	switch (dState) {
		case DEV_MAIN_MENU:
			for (int i = 0; i < 4; i++) {
				if (i == devMenuSelect)
					DrawText(devXPos + 8, devYPos + 41 + (i * 9), 0xffff, width - 16,
						devMenuOpts[i]);
				else
					DrawText(devXPos + 8, devYPos + 41 + (i * 9), RGBA8_to_RGB565(0xf6878dff),
						width - 16, devMenuOpts[i]);			
			}
			break;
		default:
			break;
	};
}

void DisplayScriptError(int objIndex, int spriteLayer) {
	PauseMusic();
	int devXPos = bufferSizeX / 2 - (width / 2);
	int devYPos = bufferSizeY / 2 - (height / 2);

	lua_State* L = objs[spriteLayer][objIndex];

	if (renderType == SUPERX_SW_RENDER) {
		DrawRectangleSW(devXPos, devYPos, width, height, 0xF807);
	}

	const char* errMsg1 = lua_tostring(L, -1);
	const char* errMsg2 = lua_tostring(L, -2);

	DrawText(devXPos + 8, devYPos + 8, 0xffff, width - 16, "SCRIPT ERROR");
	DrawText(devXPos + 8, devYPos + 35, 0xffff, width - 16, "%s %s", errMsg1, errMsg2);
	DrawText(devXPos + 8, devYPos + 17, 0xffff, width - 16, "Object will be disabled.");

	FreeObject(objIndex, spriteLayer);

	PrintLog("ERROR: %s%s\n", errMsg1, errMsg2);
}

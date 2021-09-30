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

static const u32 colUnselect = 0xf6878dff;

int devXPos, devYPos;
int entryOffset;

SceneCategory* selectedCategory;

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

	devXPos = screenWidth / 2 - (width / 2);
	devYPos = screenHeight / 2 - (height / 2);
	
	devMenuSelect = 0;
	entryOffset = 0;
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

	switch(dState) {
		case DEV_MAIN_MENU:
			if (devMenuSelect >= 4)
				devMenuSelect = 0;
			if (devMenuSelect < 0)
				devMenuSelect = 3;

			if (select) {
				switch (devMenuSelect) {
					case 0:
						ResumeMusic();
						engineState = SUPERX_MAINGAME;
						break;
					// TODO: cases 1 and 2 (restarting and selecting scenes)
					case 2:
						dState = DEV_CATEGORY_SELECT;
						devMenuSelect = 0;
						break;
					case 3:
						engineState = SUPERX_EXIT;
						break;
				};
			}
			break;
		case DEV_CATEGORY_SELECT:
			if (devMenuSelect >= categoryCount) {
				devMenuSelect = 0;
				entryOffset = 0;
			}

			if (devMenuSelect < 0) {
				devMenuSelect = categoryCount - 1;
			}

			if (devMenuSelect >= DEVMENU_MAX_ENTRIES) {
				entryOffset++;
			}

			if (devMenuSelect < entryOffset) {
				entryOffset--;
			}

			if (select) {
				// stuff
				selectedCategory = &sceneTree[devMenuSelect];
				dState = DEV_SCENE_SELECT;
				devMenuSelect = 0;
				break;
			}

			break;
		case DEV_SCENE_SELECT:
			if (devMenuSelect >= selectedCategory->sceneCount) {
				devMenuSelect = 0;
				entryOffset = 0;
			}

			if (devMenuSelect < 0) {
				devMenuSelect = selectedCategory->sceneCount - 1;
			}

			if (devMenuSelect >= DEVMENU_MAX_ENTRIES) {
				entryOffset++;
			}

			if (devMenuSelect < entryOffset) {
				entryOffset--;
			}

			if (select) {
				// TODO: scene loading isn't yet implemented; implement this once you have
				// that up and running
			}

			break;
		default:
			break;
	};
}

void RunDevMenu() {
	DrawRectangle(devXPos, devYPos, width, height, 0xff0000ff);

	switch (dState) {
		case DEV_MAIN_MENU:
			DrawText(devXPos + 8, devYPos + 8, 0xffffffff, width - 8, "WELCOME TO SUPERX DEVELOPER MENU");
			DrawText(devXPos + 8, devYPos + 17, 0xffffffff, width - 8, "SuperX, commit: %s", COMMIT);
			DrawText(devXPos + 8, devYPos + 26, 0xffffffff, width - 8, gameName);
			DrawText(devXPos + 8, devYPos + 35, 0xffffffff, width - 8, gameVersion);

			for (int i = 0; i < 4; i++) {
				if (i == devMenuSelect)
					DrawText(devXPos + 8, devYPos + 53 + (i * 9), 0xffffffff, width - 16,
						devMenuOpts[i]);
				else
					DrawText(devXPos + 8, devYPos + 53 + (i * 9), colUnselect,
						width - 16, devMenuOpts[i]);			
			}
			break;
		case DEV_CATEGORY_SELECT:
			DrawText(devXPos + 8, devYPos + 8, 0xffffffff, width - 8, "SELECT SCENE CATEGORY");

			for (int i = 0; i < DEVMENU_MAX_ENTRIES; i++) {
				if (i + entryOffset >= categoryCount)
					break;

				if (i + entryOffset == devMenuSelect)
					DrawText(devXPos + 8, devYPos + 26 + (i * 9), 0xffffffff, width - 16,
							sceneTree[i + entryOffset].categoryName);
				else
					DrawText(devXPos + 8, devYPos + 26 + (i* 9), 
							colUnselect, width - 16, sceneTree[i + entryOffset].categoryName);
			}
			break;
		case DEV_SCENE_SELECT:
			DrawText(devXPos + 8, devYPos + 8, 0xffffffff, width - 8, "SELECT A SCENE");

			for (int i = 0; i < DEVMENU_MAX_ENTRIES; i++) {
				if (i + entryOffset >= selectedCategory->sceneCount)
					break;

				if (i + entryOffset == devMenuSelect)
					DrawText(devXPos + 8, devYPos + 26 + (i * 9), 0xffffffff, width - 16,
							selectedCategory->scenes[i + entryOffset].sceneName);
				else
					DrawText(devXPos + 8, devYPos + 26 + (i * 9), colUnselect, width - 16,
							selectedCategory->scenes[i + entryOffset].sceneName);
			}
			break;
		default:
			break;
	};
}

void DisplayScriptError(int objIndex, int spriteLayer) {
	PauseMusic();
	int devXPos = screenWidth / 2 - (width / 2);
	int devYPos = screenHeight / 2 - (height / 2);

	lua_State* L = objs[spriteLayer][objIndex];

	DrawRectangle(devXPos, devYPos, width, height, 0xff0000ff);

	const char* errMsg1 = lua_tostring(L, -1);
	const char* errMsg2 = lua_tostring(L, -2);

	DrawText(devXPos + 8, devYPos + 8, 0xffffff, width - 16, "SCRIPT ERROR");
	DrawText(devXPos + 8, devYPos + 35, 0xffffff, width - 16, "%s %s", errMsg1, errMsg2);
	DrawText(devXPos + 8, devYPos + 17, 0xffffff, width - 16, "Object will be disabled.");

	FreeObject(objIndex, spriteLayer);

	PrintLog("ERROR: %s%s\n", errMsg1, errMsg2);
}

void DisplayPaletteOverlay() {
	for (int i = 0; i < 4; i++) {
		int offsetX = screenWidth - (34 * (4 - i));
		DrawText(offsetX, screenHeight - 42, 0xffffff, width - 16, "pal%d", i);
		for (int p = 0; p < 256; p++) {
			DrawRectangle(offsetX + (p % 16) * 2, screenHeight - 32 + (p / 16) * 2, 2, 2, GetPaletteEntry(i, p));
		}
	}
}

#include "SuperX.h"

static const int width = 320;
static const int height = 175;

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
	int devXPos = bufferSizeX / 2 - (width / 2);
	int devYPos = bufferSizeY / 2 - (height / 2);

	if (renderType == SUPERX_SW_RENDER) {
		DrawRectangleSW(devXPos, devYPos, width, height, 0xF807);
	}

	DrawText(devXPos + 8, devYPos + 8, 0xffff, width - 8, "WELCOME TO SUPERX DEVELOPER MENU");
	DrawText(devXPos + 8, devYPos + 17, 0xffff, width - 8, "SuperX, commit: %s", COMMIT);
}

void RunDevMenu() {

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

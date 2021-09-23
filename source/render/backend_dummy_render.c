#include "../SuperX.h"

int InitDummyRender() {
	return 0;
}

void UpdateDummyRender() { }
void ExitDummyRender() { }

void DummyFrameLimitStart() { }
void DummyFrameLimitEnd() { }

void DummyClearScreen(int color) {
	PrintLog("NOTE: unimplemented call (ClearScreen)\n");
}

void DummyDrawSprite(int sheetID, int x, int y, int sx, int sy, int width, int height, SpriteFlipFlag flag) {
	PrintLog("NOTE: unimplemented call (DrawSprite)\n");
}

void DummyDrawRectangle(int x, int y, int w, int h, u32 color) {
	PrintLog("NOTE: unimplemented call (DrawRectangle)\n");
}

void DummyDrawCharacter(int, int, char, u32) {
	PrintLog("NOTE: unimplemented call (DrawCharacter)\n");
}

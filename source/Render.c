#include "SuperX.h"

RenderBackendFeatures backendFeatures;

// --- --- START FUNCTION POINTERS --- ---

int (*RenderBackendInit)();
void (*RenderBackendUpdate)();
void (*RenderBackendExit)();

void (*FrameLimitStart)();
void (*FrameLimitEnd)();

void (*ClearScreen)(int color);

void (*DrawSprite)(int, int, int, int, int, int, int, SpriteFlipFlag);
void (*DrawRectangle)(int, int, int, int, u32);

void (*DrawCharacter)(int, int, char, u32);

// --- --- END FUNCTION POINTERS --- ---


// --- --- START RENDER VARIABLES --- ---
int screenWidth;
int screenHeight;
// --- --- END RENDER VARIABLES --- ---

int SetRenderBackend(SuperXRenderType rType) {
	switch (renderType) {
		case SUPERX_SW_RENDER:
			RenderBackendInit   = InitSWBackend;
			RenderBackendUpdate = UpdateSWBackend;
			RenderBackendExit   = ExitSWBackend;

			ClearScreen   = ClearScreenSW;
			DrawSprite    = DrawSpriteSW;
			DrawRectangle = DrawRectangleSW;
			DrawCharacter = DrawCharacterSW;

			FrameLimitStart = SWFrameLimitStart;
			FrameLimitEnd   = SWFrameLimitEnd;

			renderType = rType;
			break;
		default:
			// TODO: dummy draw calls

			renderType = SUPERX_DUMMY_RENDER;
			break;
	};

	return RenderBackendInit();
}

void DrawText(int x, int y, u32 color, int width, const char* text, ...) {
	char buf[0x100];

	va_list args;
	va_start(args, text);
	vsprintf(buf, text, args);	

	char* s = (char*) buf;
	int px = x;
	int py = y;
	int w = 0;
	while (*s != '\0') {
		if (renderType == SUPERX_SW_RENDER) {
			DrawCharacterSW(px, py, *s, color);
		}

		s++;
		w += 8;
		px += FONTCHR_WIDTH;

		if (w >= width && width != -1) {
			w = 0;
			px = x;
			py += FONTCHR_HEIGHT + 1;
		}
	}
}

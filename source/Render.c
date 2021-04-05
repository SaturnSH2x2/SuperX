#include "SuperX.h"

// --- frameBuffer variables ---
int bufferSizeX;
int bufferSizeY;

u16* frameBuffer;

// --- SDL variables ---
SDL_Surface* gameWindow;
SDL_Surface* screenBuffer;

// --- frameBuffer operations (SW rendering) ---
int CreateFrameBuffer(int x, int y) {
	frameBuffer = (u16*) malloc(x * y * sizeof(u16));
	if (!frameBuffer) {
		return 1;	
	}

	memset(frameBuffer, 0, sizeof(frameBuffer));

	bufferSizeX = x;
	bufferSizeY = y;

	return 0;
}

void DrawSpriteSW(int sheetID, int x, int y, int sx, int sy, int width, int height) {
	if (spriteSheetTable[sheetID].hasPalette) {
		// TODO: implement paletted graphics first
	} else {
		u16* srcPtr = (u16*) (spriteSheetTable[sheetID].pixelData) + spriteSheetTable[sheetID].width * sy + sx;
		u16* dstPtr = (u16*) (frameBuffer) + bufferSizeX * y + x;

		for (int dy = 0; dy < height; dy++) {
			for (int dx = 0; dx < width; dx++) {
				*dstPtr = *srcPtr;
				srcPtr++;
				dstPtr++;
			}

			srcPtr += spriteSheetTable[sheetID].width - width;
			dstPtr += bufferSizeX - width;
		}
	}
}

void ClearFrameBuffer(u16 color) {
	for (int i = 0; i < bufferSizeX * bufferSizeY; i++) {
		frameBuffer[i] = (u16) color;
	}
}

void ReleaseFrameBuffer() {
	free(frameBuffer);
}


// --- SDL boilerplate code ---
void UpdateScreenSDL() {
	if (bufferSizeX == gameWindow->w && bufferSizeY == gameWindow->h) {
		memcpy(screenBuffer->pixels, frameBuffer, bufferSizeX * bufferSizeY * sizeof(u16));
	} else {
		// SDL 1.2 doesn't have any built-ins for surface scaling, so we have to do it manually
		float xratio = gameWindow->w  / bufferSizeX;
		float yratio = gameWindow->h  / bufferSizeY;

		u16* ptr = (u16*) screenBuffer->pixels;

		for (int y = 0; y < gameWindow->h; y++) {
			for (int x = 0; x < gameWindow->w; x++) {
				int dx = (int) (x / xratio);
				int dy = (int) (y / yratio);

				*ptr = frameBuffer[dy * bufferSizeX + dx];
				ptr++;
			}
		}
	}
	SDL_BlitSurface(screenBuffer, NULL, gameWindow, NULL);
	
	SDL_Flip(gameWindow);
}

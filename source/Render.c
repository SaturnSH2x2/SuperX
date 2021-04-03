#include "SuperX.h"

// --- frameBuffer variables ---
int bufferSizeX;
int bufferSizeY;

u16* frameBuffer;

// --- SDL variables ---
SDL_Surface* gameScreen;

// --- frameBuffer operations (SW rendering) ---
int CreateFrameBuffer(int x, int y) {
	frameBuffer = (u16*) malloc(bufferSizeX * bufferSizeY * sizeof(u16));
	if (!frameBuffer) {
		return 1;	
	}

	memset(frameBuffer, 0, sizeof(frameBuffer));
	return 0;
}

void ClearFrameBuffer(u16 color) {
	for (int y = 0; y < bufferSizeY; y++) {
		for (int x = 0; x < bufferSizeX; x++) {
			frameBuffer[y * bufferSizeX + x] = color;
		}
	}
}

void ReleaseFrameBuffer() {
	free(frameBuffer);
}


// --- SDL boilerplate code ---
void UpdateScreenSDL() {
	// TODO: scale and copy framebuffer to screen
	
	SDL_Flip(gameScreen);
}

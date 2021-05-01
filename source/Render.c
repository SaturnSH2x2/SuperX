#include "SuperX.h"

// --- frameBuffer variables ---
int bufferSizeX;
int bufferSizeY;

u16* frameBuffer;

// --- SDL variables ---
SDL_Window* gameWindow;
SDL_Renderer* renderer;
SDL_Texture* bufferTexture;

// --- frameBuffer operations (SW rendering) ---
int CreateFrameBuffer(int x, int y) {
	frameBuffer = (u16*) malloc(x * y * sizeof(u16));
	if (!frameBuffer) {
		return 1;	
	}

	memset(frameBuffer, 0, bufferSizeX * bufferSizeY * sizeof(u16));

	bufferSizeX = x;
	bufferSizeY = y;

	bufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB565, 
				SDL_TEXTUREACCESS_STREAMING, bufferSizeX, bufferSizeY);
	if (!bufferTexture) {
		PrintLog("ERROR: could not allocate bufferTexture\n");
		return 1;
	}


	return 0;
}

// TODO: account for PivotX/PivotY
void DrawSpriteSW(int sheetID, int x, int y, int sx, int sy, int width, int height, SpriteFlipFlag flag) {
	if (x >= bufferSizeX || y >= bufferSizeY || x + width < 0 || y + height < 0) {
		//PrintLog("NOTE: DrawSprite call coordinates draw offscreen. Ignoring.\n");
		return;
	}

	if (sx >= spriteSheetTable[sheetID].width || sx < 0 || sy >= spriteSheetTable[sheetID].height || sy < 0 ||
			sx + width >= spriteSheetTable[sheetID].width || sy + height >= spriteSheetTable[sheetID].height) {
		PrintLog("ERROR: (DrawSprite) Invalid sprite coordinates passed. Ignoring.\n");
		return;
	}

	if (spriteSheetTable[sheetID].hasPalette) {
		// TODO: implement paletted graphics first
	} else {
		u16* srcPtr = (u16*) (spriteSheetTable[sheetID].pixelData) + spriteSheetTable[sheetID].width * sy + sx;
		u16* dstPtr = (u16*) (frameBuffer) + bufferSizeX * y + x;

		switch (flag) {
			case XFLIP:
				srcPtr += width;
				for (int dy = 0; dy < height; dy++) {
					for (int dx = 0; dx < width; dx++) {
						if (*srcPtr != 0xf81f && x + dx < bufferSizeX && x + dx >= 0 &&
								y + dy < bufferSizeY && y + dy >= 0)
							*dstPtr = *srcPtr;

						srcPtr--;
						dstPtr++;
					}

					if (dy >= bufferSizeY)
						break;

					srcPtr += spriteSheetTable[sheetID].width + width;
					dstPtr += bufferSizeX - width;
				}

				break;
			case YFLIP:
				srcPtr += spriteSheetTable[sheetID].width * height;
				for (int dy = 0; dy < height; dy++) {
					for (int dx = 0; dx < width; dx++) {
						if (*srcPtr != 0xf81f && x + dx < bufferSizeX && x + dx >= 0 &&
									y + dy < bufferSizeY && y + dy >= 0)
							*dstPtr = *srcPtr;

						srcPtr++;
						dstPtr++;
					}

					if (dy >= bufferSizeY)
						break;

					srcPtr -= spriteSheetTable[sheetID].width + width;
					dstPtr += bufferSizeX - width;
				}

				break;
			case XYFLIP:
				srcPtr += spriteSheetTable[sheetID].width * height + width;
				for (int dy = 0; dy < height; dy++) {
					for (int dx = 0; dx < width; dx++) {
						if (*srcPtr != 0xf81f && x + dx < bufferSizeX && x + dx >= 0
								&& y + dy < bufferSizeY && y + dy >= 0)
							*dstPtr = *srcPtr;

						srcPtr--;
						dstPtr++;
					}

					if (dy >= bufferSizeY)
						break;

					srcPtr -= spriteSheetTable[sheetID].width - width;
					dstPtr += bufferSizeX - width;
				}

				break;
			default:
				for (int dy = 0; dy < height; dy++) {
					for (int dx = 0; dx < width; dx++) {
						if (*srcPtr != 0xf81f && x + dx < bufferSizeX && x + dx >= 0
								&& y + dy < bufferSizeY && y + dy >= 0) 
							*dstPtr = *srcPtr;

						srcPtr++;
						dstPtr++;
					}

					if (dy >= bufferSizeY)
						break;

					srcPtr += spriteSheetTable[sheetID].width - width;
					dstPtr += bufferSizeX - width;
				}

				break;
		}
	}
}

// TODO: implementation slightly borked, fix bleed-over
void DrawRectangleSW(int x, int y, int w, int h, u16 color) {
	u16* ptr = (u16*) (frameBuffer) + y * bufferSizeX + x;
	for (int dy = 0; dy < h; dy++) {
		if (dy + y < 0) {
			ptr += bufferSizeX;
			continue;
		}

		if (dy + y >= bufferSizeY)
			break;

		for (int dx = 0; dx < w; dx++) {
			if (dx + x >= bufferSizeX || dx + x < 0) {
				ptr++;
				continue;
			}

			*ptr = color;
			ptr++;
		}

		ptr += bufferSizeX - w;
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
	SDL_UpdateTexture(bufferTexture, NULL, frameBuffer, bufferSizeX * sizeof(u16));

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, bufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);	
}

#include "../SuperX.h"
#include "SystemText.h"

// TODO: replace u16 args with u32 and convert at draw time

// --- frameBuffer variables ---
int bufferSizeX = DEFAULT_INTERNALSIZEX;
int bufferSizeY = DEFAULT_INTERNALSIZEY;

int start, end;

u16* frameBuffer;

// --- SDL variables ---
SDL_Window* gameWindow;
SDL_Renderer* renderer;
SDL_Texture* bufferTexture;

int InitSWBackend() {
	if (CreateFrameBuffer()) {
		PrintLog("ERROR: failed to allocate frameBuffer\n");
		return 1;
	}

	screenWidth  = bufferSizeX;
	screenHeight = bufferSizeY;

	return 0;
}

void UpdateSWBackend() {
#if SUPERX_USING_SDL2
	UpdateScreenSDL();	
#endif
}

void ExitSWBackend() {
	ReleaseFrameBuffer();
}

void SWFrameLimitStart() {
	start = SDL_GetTicks();
}

void SWFrameLimitEnd() {
	end = SDL_GetTicks();
	if (end - start < 1000.0f / frameRate) {
		SDL_Delay( (1000.0f / frameRate) - (end - start) );
	}

}

// --- frameBuffer operations (SW rendering) ---
int CreateFrameBuffer() {
	frameBuffer = (u16*) malloc(bufferSizeX * bufferSizeY * sizeof(u16));
	if (!frameBuffer) {
		return 1;	
	}

	memset(frameBuffer, 0, bufferSizeX * bufferSizeY * sizeof(u16));

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

	if (		sx >= spriteSheetTable[sheetID].width || sx < 0 ||
			sy >= spriteSheetTable[sheetID].height || sy < 0 ||
			sx + width > spriteSheetTable[sheetID].width || 
			sy + height > spriteSheetTable[sheetID].height) {
		PrintLog("ERROR: (DrawSprite) Invalid sprite coordinates passed (x: %d, y: %d, sx: %d, sy: %d). Ignoring.\n", x, y, sx, sy);
		return;
	}

	if (spriteSheetTable[sheetID].hasPalette) {
		u8* srcPtr = (u8*) (spriteSheetTable[sheetID].pixelData) + spriteSheetTable[sheetID].width * sy + sx;
		u16* dstPtr = (u16*) (frameBuffer) + bufferSizeX * y + x;

		int i = spriteSheetTable[sheetID].paletteIndex;

		switch (flag) {
			case XFLIP:
				srcPtr += width;
				for (int dy = 0; dy < height; dy++) {
					for (int dx = 0; dx < width; dx++) {
						if (*srcPtr != transparentColor[i] && 
								x + dx < bufferSizeX && x + dx >= 0 &&
								y + dy < bufferSizeY && y + dy >= 0)
							*dstPtr = colorPalette[(i * 256) + *srcPtr];

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
						if (*srcPtr != transparentColor[i] && 
								x + dx < bufferSizeX && x + dx >= 0 &&
								y + dy < bufferSizeY && y + dy >= 0)
							*dstPtr = colorPalette[(i * 256) + *srcPtr];

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
						if (*srcPtr != transparentColor[i] && 
								x + dx < bufferSizeX && x + dx >= 0 &&
								y + dy < bufferSizeY && y + dy >= 0)
	
							*dstPtr = colorPalette[(i * 256) + *srcPtr];

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
						if (*srcPtr != transparentColor[i] && 
								x + dx < bufferSizeX && x + dx >= 0 &&
								y + dy < bufferSizeY && y + dy >= 0)
	

							*dstPtr = colorPalette[(i * 256) + *srcPtr];

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

void DrawRectangleSW(int x, int y, int w, int h, u32 color) {
	u16 color16 = RGBA8_to_RGB565(0xff << 24 | color);
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

			*ptr = color16;
			ptr++;
		}

		ptr += bufferSizeX - w;
	}
}

void DrawCharacterSW(int x, int y, char c, u32 color) {
	u16 color16 = RGBA8_to_RGB565(0xff << 24 | color);
	char* src = (char*) (fontPixelData) + (c * FONTCHR_WIDTH);
	u16* dst = (u16*) (frameBuffer) + y * bufferSizeX + x;
	for (int dy = 0; dy < FONTCHR_HEIGHT; dy++) {
		if (y + dy < 0 || y + dy >= bufferSizeY) {
			dst += bufferSizeX - FONTCHR_WIDTH;
			src += FONTDATA_WIDTH - FONTCHR_WIDTH;
			continue;
		}

		for (int dx = 0; dx < FONTCHR_WIDTH; dx++) {
			if (x + dx < 0 || x + dx >= bufferSizeX) {
				src++;
				dst++;
				continue;
			}

			if (*src == 1) 
				*dst = color16;

			src++;
			dst++;
		}

		dst += bufferSizeX - FONTCHR_WIDTH;
		src += FONTDATA_WIDTH - FONTCHR_WIDTH;
	}
}



void ClearFrameBuffer(u16 color) {
	for (int i = 0; i < bufferSizeX * bufferSizeY; i++) {
		frameBuffer[i] = (u16) color;
	}
}

void ClearScreenSW(int color) {
	ClearFrameBuffer(RGBA8_to_RGB565(0xff000000 | color));
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

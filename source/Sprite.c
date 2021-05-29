#include "SuperX.h"

SpriteSheet spriteSheetTable[MAX_SPRITESHEET_COUNT];
u8 usedSpriteSheets = 0;

void ClearAllSpriteSheets() {
	for (u8 i = 0; i < usedSpriteSheets; i++) {
		free(spriteSheetTable[i].pixelData);
	}
}

// loads pixel data from PNG and puts it into spritesheet
// TODO: PNGs support palettes! add some detection or something
int LoadSpriteSheetFromPNG(const char* fileName, u8* sheetIndex) {
	unsigned int error;
	unsigned char* pixelData = NULL;
	unsigned int width, height;

	// load raw pixel data into memory
	error = lodepng_decode32_file(&pixelData, &width, &height, fileName);
	if (error) {
		PrintLog("ERROR: loading %s, %s\n", fileName, lodepng_error_text(error));
		return 1;
	}

	// allocate memory for new sprite sheet
	if (usedSpriteSheets >= MAX_SPRITESHEET_COUNT) {
		PrintLog("ERROR (LoadSpriteFromPNG): exceeded max number of spritesheets\n");
		return 1;
	}

	spriteSheetTable[usedSpriteSheets].pixelData = malloc(width * height * sizeof(u16));
	if (!spriteSheetTable[usedSpriteSheets].pixelData) {
		PrintLog("ERROR (LoadSpriteFromPNG): could not allocate memory for spritesheet\n");
		return 1;
	}

	*sheetIndex = usedSpriteSheets;
	usedSpriteSheets++;

	// copy pixel data into memory
	u32* srcPtr = (u32*) pixelData;
	u16* dstPtr = (u16*) spriteSheetTable[*sheetIndex].pixelData;
	for (unsigned int i = 0; i < width * height; i++) {
		*dstPtr = RGBA8_to_RGB565(*srcPtr);
		dstPtr++;
		srcPtr++;
	}

	// set attributes
	spriteSheetTable[*sheetIndex].width = width;
	spriteSheetTable[*sheetIndex].height = height;
	spriteSheetTable[*sheetIndex].hasPalette = 0;

	PrintLog("NOTE: Loading %s into index %d, w: %d, h: %d\n", fileName, *sheetIndex, width, height);

	// free original pixel data
	free(pixelData);

	return 0;
}

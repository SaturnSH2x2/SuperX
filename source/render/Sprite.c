#include "../SuperX.h"

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

// TODO: overhaul palette loading with the following options:
//  * overwrite -> overwrites entire palette with palette data from GIF
//  * append    -> append colors to palette (increment a colorsUsed variable?) (offset indices)
//  * ignore    -> keep indices, don't load palette
//  append mode seems handy for users that just converted their assets to GIF, while overwrite mode
//  seems better suited for users making conscious use of the color palettes, with colors arranged with
//  possible palette cycling in mind
int LoadSpriteSheetFromGIF(const char* fileName, u8* sheetIndex, int paletteSlot, u8 loadPalette) {
	gd_GIF* gif = gd_open_gif(fileName);
	if (!gif) {
		PrintLog("ERROR: could not load gif %d\n", fileName);
		return 1;
	}

	PrintLog("NOTE: Loading %s, w: %d, h: %d, palette size: %d\n", fileName, gif->width, gif->height, gif->palette->size);

	if (loadPalette) {
		PrintLog("NOTE: loading color palette from file into palette slot %d\n", paletteSlot);

		if (paletteSlot < 0 || paletteSlot >= 4) {
			PrintLog("ERROR: invalid palette slot %d passed\n", paletteSlot);
			gd_close_gif(gif);
			return 1;
		}

		if (gif->palette->size != 256) {
			PrintLog("ERROR: palette must be of size 256 to be copied, size: %d\n", gif->palette->size);
			gd_close_gif(gif);
			return 1;
		}

		u8* ptr = gif->palette->colors;
		u8 r, g, b;
		u32 builtColor;

		// gifdec seems to store color in RGB888, convert accordingly
		for (int i = 0; i < 256; i++) {
			r = *ptr;
			ptr++;
			g = *ptr;
			ptr++;
			b = *ptr;
			ptr++;

			builtColor = 0xff << 24 | b << 16 | g << 8 | r;
			colorPalette32[(paletteSlot * 256) + i] = builtColor;
			colorPalette[(paletteSlot * 256) + i] = RGBA8_to_RGB565(builtColor);
		}
	}

	// we only need the first frame, so get that and render
	gd_get_frame(gif);

	// load indexed pixel data into memory
	if (usedSpriteSheets >= MAX_SPRITESHEET_COUNT) {
		PrintLog("ERROR (LoadSpriteFromGIF): exceeded max number of spritesheets\n");
		return 1;
	}

	spriteSheetTable[usedSpriteSheets].pixelData = malloc(gif->width * gif->height * sizeof(u8));
	if (!spriteSheetTable[usedSpriteSheets].pixelData) {
		PrintLog("ERROR (LoadSpriteFromGIF): could not allocate memory for spritesheet\n");
		return 1;
	}

	*sheetIndex = usedSpriteSheets;
	usedSpriteSheets++;

	spriteSheetTable[*sheetIndex].width = gif->width;
	spriteSheetTable[*sheetIndex].height = gif->height;
	spriteSheetTable[*sheetIndex].hasPalette = 1;
	spriteSheetTable[*sheetIndex].paletteIndex = paletteSlot;

	u8* dest = (u8*) spriteSheetTable[*sheetIndex].pixelData;
	u8* src =  (u8*) gif->frame;
	for (int i = 0; i < gif->width * gif->height; i++) {
		*dest = *src;
		dest++;
		src++;
	}

	PrintLog("NOTE: loaded %s into index %d\n", fileName, *sheetIndex);

	gd_close_gif(gif);	
	return 0;
}

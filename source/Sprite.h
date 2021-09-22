#ifndef SPRITE_H
#define SPRITE_H

// --- definitions ---
#define MAX_SPRITESHEET_COUNT 24

// --- enumerations ---
typedef struct {
	int width;
	int height;
	void* pixelData;
	char hasPalette;
	int paletteIndex;
} SpriteSheet;

typedef enum {
	PALMODE_OVERWRITE = 0,	// overwrite entirety of the palette
	PALMODE_APPEND    = 1,  // append color entries in GIF to existing palette
	PALMODE_IGNORE    = 2,  // ignore given palette, load in indices (for reused palettes)
	PALMODE_UNINDEXED = 3   // load pixel data in unpaletted (not recommended)
} PaletteMode;

// --- variables (SW render) ---
extern SpriteSheet spriteSheetTable[MAX_SPRITESHEET_COUNT];
extern u8 usedSpriteSheets;

// --- functions (SW render) ---
void ClearAllSpriteSheets();
int LoadSpriteSheetFromPNG(const char* fileName, u8* sheetIndex);
int LoadSpriteSheetFromGIF(const char* fileName, u8* sheetIndex, int paletteSlot, u8 loadPalette);

// --- inline functions ---
// modified from https://afterthoughtsoftware.com/posts/convert-rgb888-to-rgb565
// this may be endian-dependent; maybe you should do a platform check?
inline u16 RGBA8_to_RGB565(u32 color) {
	u8 a1 = color >> 24;
	if (a1 == 0)
		return 0xF81F;

	u8 b1 = (color & 0x00FF0000) >> 16;
	u8 g1 = (color & 0x0000FF00) >> 8;
	u8 r1 = color & 0x000000FF;

	u16 b2 = (b1 >> 3) & 0x1f;
	u16 g2 = ((g1 >> 2) & 0x3f) << 5;
	u16 r2 = ((r1 >> 3) & 0x1f) << 11;

	return (r2 | g2 | b2);
}


#endif

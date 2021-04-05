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
} SpriteSheet;

// --- variables (SW render) ---
extern SpriteSheet spriteSheetTable[MAX_SPRITESHEET_COUNT];
extern u8 usedSpriteSheets;

// --- functions (SW render) ---
void ClearAllSpriteSheets();
int LoadSpriteSheetFromPNG(const char* fileName, u8* sheetIndex);

// --- inline functions ---
// modified from https://afterthoughtsoftware.com/posts/convert-rgb888-to-rgb565
inline u16 RGBA8_to_RGB565(u32 color) {
	u8 a1 = color & 0xFF000000 >> 24;
	if (a1 == 0)
		return 0xF81F;

	u8 r1 = color & 0x00FF0000 >> 16;
	u8 g1 = color & 0x0000FF00 >> 8;
	u8 b1 = color & 0x000000FF;

	u16 b2 = (b1 >> 3) & 0x1F;
	u16 g2 = ((g1 >> 2) & 0x3F) << 5;
	u16 r2 = ((r1 >> 3) & 0x1F) << 11;

	return (r2 | g2 | b2);
}


#endif

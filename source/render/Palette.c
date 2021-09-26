#include "../SuperX.h"

u16 colorPalette[256 * 4];
u32 colorPalette32[256 * 4];

u16** paletteRef;
u32** paletteRef32;

int transparentColor[4] = { -1 };

int paletteCycleIndex[MAX_PALETTE_CYCLES];

int SetPaletteEntry(u32 color, int palette, char index) {
	if (index >= 256 || index < 0) {
		PrintLog("ERROR: attempt to set color for palette %d at %d\n", palette, index);
		return 1;
	}

	colorPalette32[palette * 256 + index] = color;
	colorPalette[palette * 256 + index] = RGBA8_to_RGB565(color);
	return 0;
}

void SetTransparentColor(char index, int palette) {
	PrintLog("NOTE: transparent color for palette %d set to index %d\n", palette, index);
	transparentColor[palette] = index;
}

// TODO: implement these for the software render backend
int RegisterPaletteCycle(char startIndex, char endIndex, int* cycleIndex) {
	return -1;
}

void PausePaletteCycle(int cycleIndex) {
	
}

void ResumePaletteCycle(int cycleIndex) {
	
}



#include "SuperX.h"

u16 colorPalette[256 * 4];
u16** paletteRef;

char transparentColor[4];

int paletteCycleIndex[MAX_PALETTE_CYCLES];

int SetPaletteEntry(u32 color, int palette, char index) {
	if (index >= 256 || index < 0) {
		PrintLog("ERROR: attempt to set color for palette %d at %d\n", palette, index);
		return 1;
	}

	colorPalette[palette * 256 + index] = color;
	return 0;
}

void SetTransparentColor(u32 color, int palette) {
	transparentColor[palette] = color;
}

// TODO: implement these for the software render backend
int RegisterPaletteCycle(char startIndex, char endIndex, int* cycleIndex) {
	return -1;
}

void PausePaletteCycle(int cycleIndex) {
	
}

void ResumePaletteCycle(int cycleIndex) {
	
}



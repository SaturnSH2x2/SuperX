#ifndef PALETTE_H
#define PALETTE_H

#define MAX_PALETTE_CYCLES 4

// SuperX uses 4 palettes of 256 colors for its software render backend.
// This is done to match the Dreamcast's color limit for indexed textures.
//
// TODO: mid-frame palette changes (a la water in Sonic games)
extern u16* colorPalette;
extern u32* colorPalette32;
extern u16** paletteRef;
extern u32** paletteRef32;

extern int transparentColor[4];

extern int paletteCycleIndex[MAX_PALETTE_CYCLES];

int InitPalettes();

int SetPaletteEntry(u32 color, int palette, char index);
u32 GetPaletteEntry(int palette, char index);
void SetTransparentColor(char index, int palette);

int RegisterPaletteCycle(char startIndex, char endIndex, int* cycleIndex);
void PausePaletteCycle(int cycleIndex);
void ResumePaletteCycle(int cycleIndex);

void DisplayPaletteOverlay();

inline void ClearAllPalettes() {
	for (int i = 0; i < 256 * 4; i++) {
		colorPalette32[i] = 0;
		colorPalette[i] = 0;
	}
}

#endif

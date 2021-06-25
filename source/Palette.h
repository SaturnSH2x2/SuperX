#ifndef PALETTE_H
#define PALETTE_H

#define MAX_PALETTE_CYCLES 4

// SuperX uses 4 palettes of 256 colors for its software render backend.
// This is done to match the Dreamcast's color limit for indexed textures.
//
// TODO: mid-frame palette changes (a la water in Sonic games)
extern u16 colorPalette[256 * 4];
extern u16** paletteRef;

extern char transparentColor[4];

extern int paletteCycleIndex[MAX_PALETTE_CYCLES];

int SetPaletteEntry(u32 color, int palette, char index);
void SetTransparentColor(u32 color, int palette);

int RegisterPaletteCycle(char startIndex, char endIndex, int* cycleIndex);
void PausePaletteCycle(int cycleIndex);
void ResumePaletteCycle(int cycleIndex);

#endif

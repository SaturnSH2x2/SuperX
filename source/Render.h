#ifndef RENDER_HPP
#define RENDER_HPP

#define FONTCHR_WIDTH  (8)
#define FONTCHR_HEIGHT (8)

typedef enum {
	NOFLIP = 0,
	XFLIP = 1,
	YFLIP = 2,
	XYFLIP = 3
} SpriteFlipFlag;

typedef enum {
	SUPERX_SW_RENDER,
	SUPERX_C2D_RENDER,
	SUPERX_PVR_RENDER,
	SUPERX_DUMMY_RENDER
} SuperXRenderType;

typedef enum {
	RENDER_REALTIME_PALETTESWAP = 0b0000000000000001,
	RENDER_MIDFRAME_PALETTESWAP = 0b0000000000000010,
	RENDER_SCANLINE_DEFORMATION = 0b0000000000000100,
	RENDER_STEREOSCOPIC_3D      = 0b0000000000001000
} RenderBackendFeatures;

extern RenderBackendFeatures backendFeatures;

// --- --- START FUNCTION POINTERS --- ---

// init, update, and exit calls for any given backend
extern int (*RenderBackendInit)();
extern void (*RenderBackendUpdate)();
extern void (*RenderBackendExit)();

// frame limiting functions (may differ depending on platform)
extern void (*FrameLimitStart)();
extern void (*FrameLimitEnd)();

// function pointers to draw calls, can be set at runtime to switch backends
extern void (*ClearScreen)(int color);

extern void (*DrawSprite)(int, int, int, int, int, int, int, SpriteFlipFlag);
extern void (*DrawRectangle)(int, int, int, int, u32);

extern void (*DrawCharacter)(int, int, char, u32);

// --- --- END FUNCTION POINTERS --- ---

// --- --- START VARIABLE POINTERS --- ---
extern int screenWidth;
extern int screenHeight;
// --- --- END VARIABLE POINTERS --- ---

// sets and initializes the appropriate render backend
int SetRenderBackend(SuperXRenderType rType);

// draw calls that basically just rely on other draw calls
void DrawText(int x, int y, u32 color, int width, const char* text, ...);

#endif

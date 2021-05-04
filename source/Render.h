#ifndef RENDER_HPP
#define RENDER_HPP

typedef enum {
	NOFLIP = 0,
	XFLIP = 1,
	YFLIP = 2,
	XYFLIP = 3
} SpriteFlipFlag;

// --- frameBuffer variables ---
extern int bufferSizeX;
extern int bufferSizeY;

extern u16* frameBuffer;

// --- SDL variables ---
extern SDL_Window* gameWindow;
extern SDL_Renderer* renderer;
extern SDL_Texture* bufferTexture;

// --- frameBuffer functions ---
int CreateFrameBuffer();
void ClearFrameBuffer(u16 color);
void DrawSpriteSW(int sheetID, int x, int y, int sx, int sy, 
		int width, int height, SpriteFlipFlag flag);
void DrawRectangleSW(int x, int y, int w, int h, u16 color);
void ReleaseFrameBuffer();

// --- SDL functions ---
void UpdateScreenSDL();

#endif

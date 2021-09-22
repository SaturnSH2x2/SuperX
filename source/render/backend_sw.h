#ifndef BACKEND_SW_H
#define BACKEND_SW_H

// --- frameBuffer variables ---
extern int bufferSizeX;
extern int bufferSizeY;

extern u16* frameBuffer;

// --- frameBuffer functions ---
int CreateFrameBuffer();
void ClearFrameBuffer(u16 color);
void ReleaseFrameBuffer();

// --- init/update/exit calls ---
int InitSWBackend();
void UpdateSWBackend();
void ExitSWBackend();

// --- frame limiting ---
void SWFrameLimitStart();
void SWFrameLimitEnd();

// --- draw calls ---
void DrawSpriteSW(int sheetID, int x, int y, int sx, int sy, 
		int width, int height, SpriteFlipFlag flag);
void DrawRectangleSW(int x, int y, int w, int h, u32 color);
void DrawCharacterSW(int x, int y, char c, u32 color);
void ClearScreenSW(int color);

#if SUPERX_USING_SDL2
// --- SDL variables ---
extern SDL_Window* gameWindow;
extern SDL_Renderer* renderer;
extern SDL_Texture* bufferTexture;

// --- SDL functions ---
void UpdateScreenSDL();
#endif

#endif

#ifndef RENDER_HPP
#define RENDER_HPP

// --- frameBuffer variables ---
extern int bufferSizeX;
extern int bufferSizeY;

extern u16* frameBuffer;

// --- SDL variables ---
extern SDL_Surface* gameWindow;
extern SDL_Surface* screenBuffer;

// --- frameBuffer functions ---
int CreateFrameBuffer(int x, int y);
void ClearFrameBuffer(u16 color);
void ReleaseFrameBuffer();

// --- SDL functions ---
void UpdateScreenSDL();

#endif

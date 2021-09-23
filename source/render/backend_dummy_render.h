#ifndef BACKEND_DUMMY_RENDER_H
#define BACKEND_DUMMY_RENDER_H

int InitDummyRender();
void UpdateDummyRender();
void ExitDummyRender();

void DummyFrameLimitStart();
void DummyFrameLimitEnd();

void DummyClearScreen(int);
void DummyDrawSprite(int, int, int, int, int, int, int, SpriteFlipFlag);
void DummyDrawRectangle(int, int, int, int, u32);

void DummyDrawCharacter(int, int, char, u32);


#endif

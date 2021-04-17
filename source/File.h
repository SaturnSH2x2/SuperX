#ifndef FILE_H
#define FILE_H

// idea to use SDL_RWops came from the RSDK decomps
#define FileIO SDL_RWops
#define fOpen(path, mode)             SDL_RWFromFile(path, mode)
#define fRead(ctx, ptr, size, max)    SDL_RWread(ctx, ptr, size, max)
#define fWrite(ctx, ptr, size, num)   SDL_RWwrite(ctx, ptr, size, num)
#define fSeek(ctx, offset, whence)    SDL_RWseek(ctx, offset, whence)
#define fTell(ctx)                    SDL_RWtell(ctx)
#define fClose(ctx)                   SDL_RWclose(ctx)

#endif

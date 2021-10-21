#ifndef FILE_H
#define FILE_H

#define MAX_DIRECTORY_LENGTH (0x100)

// idea to use SDL_RWops came from the RSDK decomps
#if SUPERX_USING_SDL_RWOPS
#define FileIO SDL_RWops
#define fOpen(path, mode)             SDL_RWFromFile(path, mode)
#define fRead(ctx, ptr, size, max)    SDL_RWread(ctx, ptr, size, max)
#define fWrite(ctx, ptr, size, num)   SDL_RWwrite(ctx, ptr, size, num)
#define fSeek(ctx, offset, whence)    SDL_RWseek(ctx, offset, whence)
#define fTell(ctx)                    SDL_RWtell(ctx)
#define fClose(ctx)                   SDL_RWclose(ctx)
#define FSEEK_SET                     RW_SEEK_SET
#define FSEEK_CUR                     RW_SEEK_CUR
#define FSEEK_END                     RW_SEEK_END
#else 
#define FileIO FILE
#define fOpen(path, mode)	      fopen(path, mode)
#define fRead(ctx, ptr, size, max)    fread(ctx, ptr, size, max)
#define fWrite(ctx, ptr, size, num)   fwrite(ctx, ptr, size, num)
#define fSeek(ctx, offset, whence)    fseek(ctx, offset, whence)
#define fTell(ctx)                    ftell(ctx)
#define fClose(ctx)                   fclose(ctx)
#define FSEEK_SET                     SEEK_SET
#define FSEEK_CUR                     SEEK_CUR
#define FSEEK_END                     SEEK_END
#endif

typedef struct {
	char filePath[0x100];
	char directory[0x100];
	int size;
	FileIO* handle;
	void *buffer;
	int readOnly;
} File;

extern int usingDataFolder;

int    LoadFile(File* f, const char* filePath, const char* mode);
int    BufferFile(File* f);
void   GetDirectory(char* dest, char* src);

inline size_t ReadFile(File* f, void* buf, size_t size, size_t max) {
	return fRead(f->handle, buf, size, max);
}

inline size_t WriteFile(File* f, void* buf, size_t size, size_t num) {
	if (f->readOnly)
		return 0;

	return fWrite(f->handle, buf, size, num);
}

inline s64 SeekFile(File* f, s64 offset, int whence) {
	return fSeek(f->handle, offset, whence);
}

inline void UnbufferFile(File* f) {
	if (f->buffer) {
		free(f->buffer);
		f->buffer = NULL;
	}
}

inline void CloseFile(File* f) {
	fClose(f->handle);
	UnbufferFile(f);
}

#endif

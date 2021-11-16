#include "SuperX.h"

int usingDataFolder = 1;

int LoadFile(File* f, const char* path, const char* mode) {
	PrintLog("FILE: loading %s\n", path);
	char realPath[255];

	if (usingDataFolder) {
		snprintf(realPath, 255, "Data/%s", path);
		f->handle = fOpen(realPath, mode);
		if (!f->handle) {
			PrintLog("ERROR: Failed to get a handle for %s\n", realPath);
			return 1;
		}

		fSeek(f->handle, 0, FSEEK_END);
		f->size = fTell(f->handle);
		fSeek(f->handle, 0, FSEEK_SET);
	} else {
		// TODO: support for archives goes here
	}

	f->buffer = NULL;

	// TODO: should this be hard-coded?
	f->readOnly = 0;

	int strLength = GetStringLength(path);

	memset(f->filePath, 0, 0x100 * sizeof(char));
	strncpy(f->filePath, path, strLength);

	memset(f->directory, 0, 0x100 * sizeof(char));
	GetDirectory(f->directory, f->filePath);

	return 0;
}

void GetDirectory(char* dest, char* src) {
	int finalSlashIndex = -1;
	char* sPtr = src;
	int i = 0;
	while (*sPtr != 0) {
		if (*sPtr == '/')
			finalSlashIndex = i;

		i++;
		sPtr++;
	}

	if (finalSlashIndex == -1) {
		PrintLog("ERROR: non-directory string passed to GetDirectory: %s\n", src);
		return;
	}

	strncpy(dest, src, finalSlashIndex);
}

int BufferFile(File* f) {
	fSeek(f->handle, 0, FSEEK_SET);
	f->buffer = malloc(f->size * sizeof(char));
	if (!f->buffer) {
		PrintLog("ERROR: could not allocate memory for file buffer, file: %s\n", f->filePath);
		return 1;
	}

	fRead(f->handle, f->buffer, 1, f->size);
	if (!f->buffer) {
		PrintLog("ERROR: could not buffer filen %d\n", f->filePath);
		free(f->buffer);
		f->buffer = NULL;
		return 1;
	}

	return 0;
}

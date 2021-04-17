#include "SuperX.h"

// heavily based on RSDKv3 decomp's logging function
void PrintLog(const char* str, ...) {
	char buf[0x100];

	// construct string
	va_list args;
	va_start(args, str);
	vsprintf(buf, str, args);
	printf("%s\n", buf);

	char fPath[0x100];
	sprintf(fPath, "%slog.txt", basePath);

	FileIO* f = fOpen(fPath, "a");
	if (f) {
		fWrite(f, &buf, GetStringLength(buf), 1);
		fClose(f);
	}
}

#ifndef STRING_H
#define STRING_H

inline int GetStringLength(const char* str) {
	char* s = (char*) str;
	int size = 0;

	while (*s != 0) {
		size++;
		s++;
	}

	return size;
}

#endif

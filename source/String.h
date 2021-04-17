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

inline void CopyString(char* dst, const char* src, int size) {
	char* d = dst;
	char* s = (char*) src;
	int sz = size;

	while (sz < size) {
		*d = *s;

		if (*s == 0)
			break;

		d++;
		s++;
	}

	d = dst + size;
	*d = 0;
}

inline void AppendString(char* dst, const char* src, int size) {
	char* d = dst;
	char* s = (char*) src;
	int sz = 0;

	while (*d != 0) {
		sz++;
		d++;
	}

	if (sz >= size)
		return;

	while (sz < size) {
		*d = *s;

		if (*s == 0)
			break;

		d++;
		s++;
	}

	d = dst + size;
	*d = 0;
}

#endif

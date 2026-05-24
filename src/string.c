#include "string.h"

#include <string.h>
#include <stdlib.h>

char* DupStr(const char* str) {
	size_t len = strlen(str) + 1;
	char* buf = malloc(len);
	if (!buf) return NULL;
	memcpy(buf, str, len);
	return buf;
}

bool MatchWildcard(const char* pat, const char* text) {
	// TODO
	return false;
}

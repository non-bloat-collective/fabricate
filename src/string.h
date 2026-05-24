#ifndef FAB_STRING_H
#define FAB_STRING_H

#include <stdbool.h>

char* DupStr(const char* str);

bool MatchWildcard(const char* pat, const char* text);

#endif

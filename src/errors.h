#ifndef FAB_ERRORS_H
#define FAB_ERRORS_H

#include <stdio.h>

extern const char* argv0;

#define ERR_INT() fprintf(stderr, "%s: Internal error\n", argv0)
#define ERR_NOFAB() fprintf(stderr, "%s: No .fab file found\n", argv0)

#endif

#include "errors.h"
#include "filesystem.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

const char* argv0;

static char* filename;

static int ParseOptions(int argc, char** argv) {
	for (int i = 1; i < argc; ++i) {
		if (argv[i][0] != '-') {
			
		} else {
			
		}
	}
	return 0;
}

static int UseFirstFabFile_Cmp(const void* a, const void* b) {
	return strcmp(((const FileInfo*)a)->name, ((const FileInfo*)b)->name);
}
static int UseFirstFabFile(void) {
	size_t count;
	FileInfo* ls = Ls(".", &count);
	if (!ls) {ERR_INT(); return 2;}

	qsort(ls, count, sizeof(*ls), UseFirstFabFile_Cmp);

	for (size_t i = 0; i < count; ++i) {
		if (ls[i].type != FILETYPE_DIR && MatchWildcard("*.fab", ls[i].name)) {
			filename = DupStr(ls[i].name);
			if (!filename) {ERR_INT(); return 2;}
			FreeLs(ls);
			return 0;
		}
	}

	FreeLs(ls);
	ERR_NOFAB();
	return 1;
}

int main(int argc, char** argv) {
	argv0 = argv[0];
	int ret;
	if ((ret = ParseOptions(argc + 1, argv - 1))) return ret;
	if (!filename && (ret = UseFirstFabFile())) return ret;
	// TODO
	return 0;
}

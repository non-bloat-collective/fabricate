#ifndef FAB_FILESYSTEM_H
#define FAB_FILESYSTEM_H

#include "vlb.h"

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <dirent.h>

typedef uint8_t FileType;
enum {
	FILETYPE_UNKNOWN,
	FILETYPE_FILE,
	FILETYPE_DIR,
	FILETYPE_SPECIAL
};

typedef struct {
	char* name;
	FileType type;
} FileInfo;

typedef struct {
	struct VLB(char) path;
	FileInfo current;
	#ifndef _WIN32
		DIR* dir;
	#else
		WIN32_FIND_DATA find;
		HANDLE file;
		bool first;
	#endif
} LsState;

FileType ProbeFileType(const char* name); // Windows already has GetFileType
bool ProbeFileInfo(const char* name, FileInfo*);

bool BeginLs(const char*, LsState*);
const FileInfo* ReadLs(LsState*);
void EndLs(LsState*);

FileInfo* Ls(const char*, size_t* count);
void FreeLs(FileInfo*);

bool Rm(const char*);
bool RmDir(const char*);

#endif

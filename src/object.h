#ifndef FAB_OBJECT_H
#define FAB_OBJECT_H

#include "vlb.h"

#include <stdint.h>
#include <stdbool.h>

typedef unsigned ObjectType;
enum {
	OBJECTTYPE_NULL,
	OBJECTTYPE_STRING,
	OBJECTTYPE_ARRAY,
	OBJECTTYPE_COW
};

typedef struct Object Object;
typedef union {
	struct {
		struct VLB(char) text;
		unsigned free : 1;
		unsigned dup : 1;
	} string;
	struct VLB(Object) array;
	struct {
		Object* obj;
		size_t off;
		size_t len;
	} cow;
} ObjectData;
struct Object {
	ObjectData data;
	ObjectType type;
	unsigned refcount;
	struct VLB(Object*) cow;
};

typedef unsigned ObjStrStorType;
enum {
	OBJSTRSTOR_STATIC, // String is read-only but always available, CoW
	OBJSTRSTOR_XFER,   // Transfer ownership of string
	OBJSTRSTOR_DUP     // String will not always be available, dup immediately
};

Object* NewObject(ObjectType);
Object* NewObjectFromStr(const char* str, size_t len, ObjStrStorType);
#define NewObjectFromLitStr(STR) (NewObjectFromStr(("" STR), sizeof(STR) - 1, OBJSTRSTOR_STATIC))
void DelObject(Object*);

bool SetObject(Object* dest, Object* src);
bool CatObject(Object* dest, Object* src);
bool CatStrToObject(Object*, const char* str, size_t len, ObjStrStorType);
#define CatLitStrToObject(OBJ, STR) (CatStrToObject((OBJ), ("" STR), sizeof(STR) - 1, OBJSTRSTOR_STATIC))

#endif

#ifndef FAB_STATE_H
#define FAB_STATE_H

#include "object.h"
//#include "lexer.h"
#include "crc.h"

typedef struct {
	uint32_t namecrc;
	char* name;
	Object* obj;
} Var;
typedef struct {
	uint32_t namecrc;
	char* name;
	struct {
		//Statement* data;
		size_t count;
	} stmts;
} Func;
typedef struct {
	struct VLB(Var) vars;
} Scope;
typedef struct {
	size_t argv;
	size_t argc;
	struct {
		Scope* cur;
		Scope* data;
		size_t len;
		size_t size;
	} scopes;
} Frame;
typedef struct State State;
struct State {
	struct {
		Object* top;
		Object** data;
		size_t len;
		size_t size;
	} stack;
	struct {
		Frame* cur;
		Frame* data;
		size_t len;
		size_t size;
	} frames;
	struct VLB(Func) funcs;
	const State* parent;
};

bool InitState(State*, const State* parent);
void FreeState(State*);

bool PushFrame(State*);
bool PushArg(State*, Object*);
bool ExpArg(State*);

bool CallBuiltin(State*, const char* name);
bool CallUserFunc(State*, const char* name);

Object* GetVar(State*, const char* name);
bool SetVar(State*, const char* name, Object*);
void DelVar(State*, const char* name);

//bool SetFunc(State*, const char* name, Statements*, size_t count);
void DelFunc(State*, const char* name);

#endif

#include "state.h"

static inline void iDelVar(Var* var) {
	free(var->name);
	//DelObject(var->obj);
}
static inline void iDelFunc(Func* func) {
	free(func->name);
	for (size_t i = 0; i < func->stmts.count; ++i) {
		//DelStmts(func->stmts.data[i]);
	}
}

bool InitState(State* state, const State* parent) {
	VLB_INIT(state->stack, 8, goto emem_1;);
	state->stack.top = NULL;

	VLB_ZINIT(state->frames);
	state->frames.cur = NULL;

	state->parent = parent;

	return true;

	emem_1:
	return false;
}
void FreeState(State* state) {
	for (size_t i = 0; i < state->stack.len; ++i) {
		//DelObject(state->stack.data[i]);
	}
	for (size_t i = 0; i < state->frames.len; ++i) {
		Frame* frame = &state->frames.data[i];
		for (size_t j = 0; j < frame->scopes.len; ++j) {
			Scope* scope = &frame->scopes.data[j];
			for (size_t k = 0; k < scope->vars.len; ++k) {
				iDelVar(&scope->vars.data[i]);
			}
		}
	}
	for (size_t i = 0; i < state->funcs.len; ++i) {
		iDelFunc(&state->funcs.data[i]);
	}
}

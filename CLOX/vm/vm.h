#ifndef clox_vm_h
#define clox_vm_h

#include "../chunk//chunk.h"
#include "../value/value.h"

#define STACK_MAX 256

typedef struct {
	Chunk* chunk;
	uint8_t* ip; 
	Value stack[STACK_MAX];
	Value* stackTop; // points to where the next value should go
} VM;

typedef enum {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(const char* source);
void push(Value value);
Value pop();

#endif
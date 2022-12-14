#include <stdlib.h>
#include "../chunk/chunk.h"
#include "../memory/memory.h"

void initChunk(Chunk* chunk) {
	// We have a chunk pointer that contains the address of a chunk instance
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL; 
	chunk->lines = NULL;
	initValueArray(&chunk->constants);
} 

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int oldCapacity = chunk->capacity;
		chunk->capacity = GROW_CAPACITY(oldCapacity);
		chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
		chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
} 

void freeChunk(Chunk* chunk) {
	FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
	FREE_ARRAY(int, chunk->lines, chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

int addConstant(Chunk* chunk, Value value) {
	// chunk->constants = ValueArray
	// ValueArray->values, count
	
	writeValueArray(&chunk->constants, value);
	// -1 is required because count holds the # of values and is not 0-indexed
	// which is what we need for indexing the ValueArray
	return chunk->constants.count - 1; 
	
}








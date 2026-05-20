#include <stdio.h>
#include <stdlib.h>

#include "chunk.h"

void init_chunk(Chunk* chunk) {
    chunk -> count = 0;
    chunk -> capacity = 0;
    chunk -> code = NULL;
    chunk -> constant_count = 0;
    chunk -> constant_capacity = 0;
    chunk -> constants = NULL;
}

void write_chunk(Chunk* chunk, uint8_t byte) {
    if(chunk -> capacity < chunk -> count + 1) { // Checks if there is no space left?
        int oldCapacity = chunk -> capacity;
        chunk -> capacity = oldCapacity < 8 ? 8 : oldCapacity * 2;
        chunk -> code = realloc(chunk -> code, chunk -> capacity * sizeof(uint8_t));
    }

    chunk -> code[chunk -> count] = byte;
    chunk -> count++;
}

void free_chunk(Chunk* chunk) {
    free(chunk -> code);
    free(chunk -> constants);

    init_chunk(chunk);
}

int add_constant(Chunk* chunk, Value value) {
    if(chunk -> constant_capacity < chunk -> constant_count + 1) {
        int oldCapacity = chunk -> constant_capacity;
        chunk -> constant_capacity = oldCapacity < 8 ? 8 : oldCapacity * 2;
        chunk -> constants = realloc(chunk -> constants, chunk -> constant_capacity * sizeof(Value));
    }

    chunk -> constants[chunk -> constant_count] = value;
    
    return chunk -> constant_count++;
}
#ifndef CHUNK_H
#define CHUNK_H

#include <stdint.h>
#include "symbol_table.h"

typedef enum {
    OP_CONSTANT,
    OP_ADD,
    OP_SUB,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_RETURN
} OpCode;

typedef struct {
    int count;
    int capacity; // Allocated size of the code array
    uint8_t* code; // Array of instructions in bytes

    int constant_count;
    int constant_capacity;
    Value* constants; // Constant pool (array of values)
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte);
void free_chunk(Chunk* chunk);
int add_constant(Chunk* chunk, Value value);

#endif
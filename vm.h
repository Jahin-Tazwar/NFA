#ifndef VM_H
#define VM_H

#include "chunk.h"
#define STACK_MAX 256

typedef struct {
    Chunk* chunk;
    uint8_t* ip; // Instruction pointer
    Value stack[STACK_MAX];
    Value* stackTop;
}

#endif
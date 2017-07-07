#include "socatan_types.h"
#include "socatan_util.h"

#include <cstddef>

#if !defined(SETTLERS_OF_CATAN_MEMORY_H)

#define PERMANENT_MEMORY_SIZE Megabytes(64)
#define FRAME_MEMORY_SIZE Megabytes(32)

typedef size_t memory_unit;

struct memory_chunk {
    uint8 *Base;
    memory_unit Size;
    memory_unit Used;
    uint16 TempCount;
};

#define AllocateStruct(MemoryChunk, type) (type *) AllocateBytes(MemoryChunk, sizeof(type))
#define AllocateArray(MemoryChunk, type, Elements) (type *) AllocateBytes(MemoryChunk, sizeof(type)*Elements)
/**
 * Allocate a certain amount of bytes in a given memory chunk.
 */
void *AllocateBytes(memory_chunk *Chunk, memory_unit Size);

struct temporary_memory {
    memory_chunk *RootMemory;
    memory_unit InitialUsed;
};

/**
 * Start a new block of temporary memory.
 */
temporary_memory BeginTemporaryMemory(memory_chunk *Base);

/**
 * End a block of temporary memory. The memory used between BeginTemporaryMemory and EndTemporaryMemory
 * (allocated by the allocation-functions) will be freed after this call.
 */
void EndTemporaryMemory(temporary_memory *Memory);

#define SETTLERS_OF_CATAN_MEMORY_H
#endif // SETTLERS_OF_CATAN_MEMORY_H

#include "socatan_memory.h"
#include "socatan_util.h"

void *AllocateBytes(memory_chunk *Chunk, memory_unit Size) {
    Assert(Chunk->Size >= Size + Chunk->Used);
    void *Result = Chunk->Base + Chunk->Used;
    Chunk->Used += Size;
    return(Result);
}

temporary_memory BeginTemporaryMemory(memory_chunk *Base) {
    temporary_memory Result = {};

    Result.RootMemory = Base;
    Result.InitialUsed = Base->Used;
    ++Base->TempCount;

    return(Result);
}

void EndTemporaryMemory(temporary_memory *Memory) {
    memory_chunk *Base = Memory->RootMemory;
    Assert(Base->Used >= Memory->InitialUsed);
    Base->Used = Memory->InitialUsed;

    Assert(Base->TempCount >= 0);
    --Base->TempCount;
}

#include "socatan_util.h"
#include "socatan.h"

#include <sys/mman.h>
#include <X11/X.h>
#include <GL/glx.h>

static Display *GlobalDisplay;

static memory_chunk
MapMemory(uint64 SizeInBytes) {
    memory_chunk Result = {};

    Result.Base = (uint8 *)mmap(0, SizeInBytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(Result.Base != MAP_FAILED) {
        Result.Size = SizeInBytes;
    }

    return(Result);
}

static void
UnmapMemory(memory_chunk *MemoryChunk) {
    munmap(MemoryChunk->Base, MemoryChunk->Size);
}

int
main() {
    bool32 Running = true;

    GlobalDisplay = XOpenDisplay(0);
    if(GlobalDisplay) {
        memory_chunk PermanentMemory = MapMemory(PERMANENT_MEMORY_SIZE);
        memory_chunk FrameMemory = MapMemory(FRAME_MEMORY_SIZE);
        input GameInput = {};
        while(Running) {
            while(XPending(GlobalDisplay)) {
                XEvent CurrentEvent;
                XNextEvent(GlobalDisplay, &CurrentEvent);

                switch(CurrentEvent.type) {
                    default: {
                        printf("X-event.\n");
                    } break;
                }
            }

            temporary_memory FrameMemoryTemp = BeginTemporaryMemory(&FrameMemory);
            UpdateGame(&PermanentMemory, &FrameMemory, &GameInput);
            EndTemporaryMemory(&FrameMemoryTemp);
        }
        UnmapMemory(&PermanentMemory);
    } else {
        printf("Failed to open Display.\n");
    }
    return(0);
}

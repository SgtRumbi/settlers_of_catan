#if !defined(SETTLERS_OF_CATAN_PLATFORM_H)

#include "socatan_opengl.h"
#include "socatan_memory.h"

struct read_entire_file_result {
    void *Content;
    int64 Length;
};

#define READ_ENTIRE_FILE_FUNCTION(Name) read_entire_file_result Name(char *FilePath, memory_chunk *MemoryChunk)
typedef READ_ENTIRE_FILE_FUNCTION(read_entire_file_function);

struct platform {
    opengl_get_proc_address *OpenGLGetProcAddressFunction;
    read_entire_file_function *ReadEntireFile;
};

extern platform Platform;

#define SETTLERS_OF_CATAN_PLATFORM_H
#endif //SETTLERS_OF_CATAN_PLATFORM_H

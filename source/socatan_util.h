#if !defined(SETTLERS_OF_CATAN_UTIL_H)

#include "socatan_types.h"

#include <malloc.h>
#include <cstdio>
#include <cstring>

#if defined(SOC_DEBUG)
#define Assert(Expr) if(!(Expr)) {printf("'%s' failed!", #Expr); *((int *)0) = 0;}
#else
#define Assert(Expr)
#endif

#define InvalidDefaultCase default: {printf("Default case is not supported! (in %s(L%d))", __FILE__, __LINE__); *((int *)0) = 0;} break

template <typename t> inline t
Pow(t Base, t Exp) {
    t Result = 1;

    for(uint32 Index = 0;
        Index < Exp;
        ++Index) {
        Result *= Base;
    }

    return(Result);
}

// TODO(js): Get rid of malloc -> Custom memory manager.
#define AllocStruct(type) ((type *)malloc(sizeof(type)))
#define AllocArray(type, Count) ((type *)malloc((Count)*sizeof(type)))

#define ZeroSize(Pointer, Size) ZeroSize_((uint8 *)Pointer, Size)
#define ZeroInstance(Instance) ZeroSize_((uint8 *)Instance, sizeof(Instance))
// TODO(js): Check if this works.
#define ZeroArray(Instance, Elements) ZeroSize_((uint8 *)Instance, sizeof(Instance[0])*Elements)
inline void
ZeroSize_(uint8 *Pointer, uint32 Size) {
    uint32 Current = Size;
    while(Current--) {
        Pointer[Current] = 0;
    }
}

#define PlatformLogInfo(...) LinuxLogInfo(__VA_ARGS__)
#define PlatformLogWarn(...) LinuxLogWarn(__VA_ARGS__)
#define PlatformLogError(...) LinuxLogError(__VA_ARGS__)

#define LinuxLogInfo(...) printf(__VA_ARGS__); printf("\n")
#define LinuxLogWarn(...) printf(__VA_ARGS__); printf("\n")
#define LinuxLogError(...) printf(__VA_ARGS__); printf("\n")

inline bool32
IsExtensionSupported(const char *ExtensionsList, const char *Extension) {
    bool32 Result = false;

    if (ExtensionsList && Extension) {
        const char *Start;
        const char *Where;
        const char *Terminator;

        Where = strchr(Extension, ' ');
        if (!Where && (*Extension != '\0')) {
            for (Start = ExtensionsList;;
                    ) {
                Where = strstr(Start, Extension);

                if (Where) {
                    Terminator = Where + strlen(Extension);

                    if ((Where == Start) || (*(Where - 1) == ' ')) {
                        if ((*Terminator == ' ') || (*Terminator == '\0')) {
                            Result = true;
                            break;
                        }
                    }

                    Start = Terminator;
                } else {
                    break;
                }
            }
        } else {
            Result = false;
        }
    }

    return (Result);
}

#define Kilobytes(KBs) ((KBs)*1024L)
#define Megabytes(MBs) (Kilobytes(MBs)*1024L)
#define Gigabytes(GBs) (Megabytes(GBs)*1024L)

#define SETTLERS_OF_CATAN_UTIL_H
#endif // SETTLERS_OF_CATAN_UTIL_H

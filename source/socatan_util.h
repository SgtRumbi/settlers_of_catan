#if !defined(SETTLERS_OF_CATAN_UTIL_H)

#include "socatan_types.h"

#include <malloc.h>

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

#define Kilobytes(KBs) ((KBs)*1024L)
#define Megabytes(MBs) (Kilobytes(MBs)*1024L)
#define Gigabytes(GBs) (Megabytes(GBs)*1024L)

#define SETTLERS_OF_CATAN_UTIL_H
#endif // SETTLERS_OF_CATAN_UTIL_H

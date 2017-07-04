#include "socatan.h"
#include "socatan_types.h"

int
main() {
    bool32 Running = true;
    input GameInput = {};
    while(Running) {
        UpdateGame(&GameInput);
        Running = false;
    }
    return(0);
}

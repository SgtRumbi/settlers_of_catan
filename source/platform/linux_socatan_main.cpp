#include "socatan.h"
#include "socatan_types.h"

int
main() {
    bool32 Running = true;
    while(Running) {
        UpdateGame();
        Running = false;
    }
    return(0);
}

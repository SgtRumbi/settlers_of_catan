#include "game.h"
#include "types.h"

int
main() {
    bool32 Running = true;
    while(Running) {
        UpdateGame();
        Running = false;
    }
    return(0);
}

#include "game.h"
#include "types.h"
#include "util.h"

#include <cstdio>

static void
BuildGameField(game_field *GameField) {
    // TODO(js): Implement
    Assert(!"Not yet implemented!");
}

void
UpdateGame() {
    //
    // NOTE(js): Explanation: This is set up in this weird way to be able to _later_ run this in a game loop -> have
    // initialisation, update and render in one call (-> Platform-layer just has to deal with one function
    // (UpdateGame()) and just calls this one every frame.)
    //
    static bool32 Initialized = false;
    static game_state GameState;
    if(!Initialized) {
        BuildGameField(&GameState.GameField);

        Initialized = true;
    }
}

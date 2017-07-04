#include "game.h"
#include "types.h"
#include "util.h"

#include <cstdio>

static void
BuildGameField(game_field *GameField) {
    // TODO(js): Implement game_field-initialisation
    // - Create graph
    //    - Create nodes, representing the meeting places of each tiles
    //    - Create edges, representing the bridges
    // - Create list of tiles
    // - Connect nodes to list of tiles -> Every node has to know where on the field he is and which tile it touches
    Assert(!"Not yet implemented!");
}

static void
InitializePlayers(player *Players, uint32 PlayerCount) {

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
        InitializePlayers(GameState.Players, GameState.PlayerCount);

        Initialized = true;
    }
}

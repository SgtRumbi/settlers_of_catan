#include "socatan.h"
#include "socatan_util.h"

#include <cstdio>

static void
SetGameMode(game_state *State, game_mode Mode) {
    switch(Mode) {
        case GameMode_StartPhase: {
            State->CurrentMode = Mode;
        } break;

        case GameMode_GamePhase: {
            State->CurrentMode = Mode;
        } break;

        InvalidDefaultCase;
    }
}

static void
BuildGameField(game_field *GameField) {
    // - Create graph
    //    - Create nodes, representing the meeting places of each tiles
    //    - Create edges, representing the bridges
    // - Create list of tiles
    // - Connect nodes to list of tiles -> Every node has to know where on the field he is and which tile it touches
    // Assert(!"Not yet implemented!");

    // Honeycomb-shape:
    //      _
    //    _/ \_
    //  _/ \_/ \_
    // / \_/ \_/ \
    // \_/ \_/ \_/
    //   \_/ \_/
    //     \_/
    //
    //
    // Nodes: Corners (30)
    // TODO(js): Make dynamic
    u8 CornerCount = 30;

    // Allocate nodes and bridges
    GameField->Nodes = AllocArray(game_field_graph_node, CornerCount);
    GameField->NodeCount = CornerCount;
    ZeroSize(GameField->Nodes, CornerCount*sizeof(game_field_graph_node));
    GameField->Bridges = AllocArray(int32, CornerCount*CornerCount);
    ZeroSize(GameField->Bridges, CornerCount*CornerCount*sizeof(int32));
}

static void
InitializePlayers(player *Players, uint32 PlayerCount) {
    // TODO(js): ID-Generator?
    uint16 IDCounter = 1;

    for(uint32 PlayerIndex = 0;
        PlayerIndex < PlayerCount;
        ++PlayerIndex) {
        Players[PlayerIndex].ID = IDCounter++;
        for(uint32 ResourceIndex = 0;
            ResourceIndex < RESOURCE_COUNT;
            ++ResourceIndex) {
            Players[PlayerIndex].Resources[ResourceIndex].Amount = 0;
            //
            // NOTE(js): The pow function is just used because the item-enum is designed in a power of 2 style way -> to
            // be able to create resource-flags
            //
            Players[PlayerIndex].Resources[ResourceIndex].Amount = Pow(2u, ResourceIndex);
        }
    }
}

void
UpdateGame(input *GameInput) {
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
        SetGameMode(&GameState, GameMode_StartPhase);

        Initialized = true;
    }

    // TODO(js): Process input

    // TODO(js): Update game
    switch(GameState.CurrentMode) {
        case GameMode_StartPhase: {

        } break;

        case GameMode_GamePhase: {

        } break;

        InvalidDefaultCase;
    }

    // TODO(js): Render game
}

#include "types.h"

#if !defined(SETTLERS_OF_CATAN_GAME_H)

enum resource_type {
    ResourceType_Wood = 0x1,
    ResourceType_Stone = 0x2,
    ResourceType_Weed = 0x4,
    ResourceType_Clay = 0x8,
    ResourceType_Sheep = 0x10,
};
// TODO(js): Find a solution.
#define RESOURCE_COUNT 5

/**
 * Type of buildings contained/'containered' by a node.
 * (In a flag-ish kind of way bc fun)
 */
enum building_type {
    BuildingType_None = 0x0,
    BuildingType_Settlement = 0x1,
    BuildingType_City = 0x2,
};

/**
 * Amount of Resources by a specific type.
 */
struct resources {
    resource_type Type;
    // NOTE(js): Overflow-check? May not be necessary, but why not...
    uint32 Amount;
};

struct player {
    uint32 ID;
    // TODO(js): De-hardcode -> Match number of resource_types.
    resources Resources[RESOURCE_COUNT];
};

/**
 * Returns the amount of resources of a specific type the player currently has on his deck.
 */
inline uint32
GetAmountOfResByType(player *Player, resource_type Type) {
    uint32 Result = 0;

    if(Player) {
        for(uint32 ResourceIndex = 0;
            ResourceIndex < RESOURCE_COUNT;
            ++ResourceIndex) {
            if(Type == Player->Resources[ResourceIndex].Type) {
                Result = Player->Resources[ResourceIndex].Amount;
            }
        }
    }

    return(Result);
}

struct building {
    building_type Type;
    player *Owner;
};

/**
 * One element of the graph representing the game field.
 */
struct game_field_graph_node {
    building *Building;
};

/**
 * The structure representing the game field -> Container for all nodes, all bridges.
 */
struct game_field {
    // The graph of for the game field:
    game_field_graph_node *Nodes;
    uint32 NodesCount;
    uint8 *Bridges;
};

struct game_state {
    game_field GameField;

    // TODO(js): De-hardcode this.
    player Players[2];
    uint32 PlayerCount = 2;
};

void UpdateGame();

#define SETTLERS_OF_CATAN_GAME_H
#endif // SETTLERS_OF_CATAN_GAME_H

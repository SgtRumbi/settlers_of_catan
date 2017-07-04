#include "socatan_types.h"

#if !defined(SETTLERS_OF_CATAN_GAME_H)

#define MAX_RESOURCES_PER_SLOT 1024

/**
 * Representing different phases of the game:
 *  - Start phase: Every player is meant to pick
 *     - a color
 *     - a starting place for his settlement
 *  - Game phase: Every player plays against each other
 */
enum game_mode {
    GameMode_StartPhase = 0,
    GameMode_GamePhase = 1
};

/**
 * Available resources in the world.
 * (In a flag-ish kind of way bc fun)
 */
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
 */
enum building_type {
    BuildingType_None = 0,
    BuildingType_Settlement = 1,
    BuildingType_City = 2,
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
    uint16 ID;
    // TODO(js): De-hardcode -> Match number of resource_types.
    resources Resources[RESOURCE_COUNT];
};

/**
 * Returns the amount of resources of a specific type the player currently has on his deck.
 *
 * TODO(js): Make resource_type take in a bit-field to get amount of multiple resources. (for example:
 * GetAmountOfResByType(..., ResourceType_Wood | ResourceType_Stone))
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

/**
 * One element of the graph representing the game field.
 *
 * Contains: A building type and the owner of the building
 */
struct game_field_graph_node {
    building_type Type;
    player *Owner;
};

struct tile {
    resource_type *ResourceType;
    uint32 DieResult;
};

/**
 * The structure representing the game field -> Container for all nodes, all bridges.
 */
struct game_field {
    // The graph of for the game field:
    game_field_graph_node *Nodes;
    uint32 NodesCount;
    // Bridges: Adjacency matrix + bridges container at the same time:
    //   -1:        No bridge can be planted because there is no connection between two nodes
    //              TODO(js): Initialisation to -1!
    //   0:         A bridge can be planted, but the spot is currently empty
    //   [1; 2e16[: Player-IDs (which player the bridge belongs to)
    int32 *Bridges;
};

struct game_state {
    game_mode CurrentMode;

    game_field GameField;

    // TODO(js): De-hardcode this.
    player Players[2];
    uint32 PlayerCount = 2;
};

void UpdateGame();

#define SETTLERS_OF_CATAN_GAME_H
#endif // SETTLERS_OF_CATAN_GAME_H

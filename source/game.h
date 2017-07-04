#include "types.h"

#if !defined(SETTLERS_OF_CATAN_GAME_H)

enum resource_type {
    ResourceType_Wood,
    ResourceType_Stone,
    ResourceType_Weed,
    ResourceType_Clay,
    ResourceType_Sheep,
};

/**
 * Type of buildings contained/'containered' by a node.
 * (In a flag-ish kind of way bc fun)
 */
enum building_type {
    BuildingType_None = 0x0,
    BuildingType_Settlement = 0x1,
    BuildingType_City = 0x2,
};

struct building {
    building_type Type;
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

struct player {
    uint32 ID;
};

struct game_state {
    game_field GameField;

    // TODO(jspies): De-hardcode this.
    player Player[2];
};

void UpdateGame();

#define SETTLERS_OF_CATAN_GAME_H
#endif // SETTLERS_OF_CATAN_GAME_H

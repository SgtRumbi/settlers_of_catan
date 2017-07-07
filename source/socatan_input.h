#if !defined(SETTLERS_OF_CATAN_INPUT_H)

#include "socatan_types.h"

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 16

struct input {
    bool32 KeysDown[MAX_KEYS];
    bool32 KeysUp[MAX_KEYS];

    u32 MousePositionX, MousePositionY;
    bool32 MouseButtonsUp[MAX_MOUSE_BUTTONS];
    bool32 MouseButtonsDown[MAX_MOUSE_BUTTONS];
};

#define SETTLERS_OF_CATAN_INPUT_H
#endif // SETTLERS_OF_CATAN_INPUT_H

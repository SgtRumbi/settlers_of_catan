#include <cstdio>
#include <x86intrin.h>
#include "socatan_types.h"

#if !defined(SETTLERS_OF_CATAN_DEBUG_H)

// TODO(js): Make working.

unsigned long long DebugCycleCounters[255];

struct cycle_counter {
    unsigned long long StartTime;
    uint64 ID;

    cycle_counter(uint64 ID) : ID(ID) {
        StartTime = __rdtsc();
        printf("Start %llu\n", StartTime);
    }

    ~cycle_counter() {
        unsigned long long dT = __rdtsc() - StartTime;
        printf("End %llu\n", dT);

        DebugCycleCounters[ID] = dT;
    }
};

#define CYCLE_COUNTER cycle_counter(__COUNTER__)

#define SETTLERS_OF_CATAN_DEBUG_H
#endif // SETTLERS_OF_CATAN_DEBUG_H

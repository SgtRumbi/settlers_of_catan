#if !defined(SETTLERS_OF_CATAN_DEBUG_H)

#include <cstdio>
#include <x86intrin.h>
#include "socatan_types.h"

// TODO(js): Make working.

unsigned long long int DebugCycleCounters[255];

struct cycle_counter {
    unsigned long long int StartTime;
    uint64 ID;

    cycle_counter(uint64 ID) : ID(ID) {
        StartTime = __rdtsc();
        printf("Start %llu\n", StartTime);
    }

    ~cycle_counter() {
        unsigned long long int dT = __rdtsc() - StartTime;
        printf("End %llu\n", dT);

        DebugCycleCounters[ID] = dT;
    }
};

#define CYCLE_COUNTER cycle_counter(__COUNTER__)

#define SETTLERS_OF_CATAN_DEBUG_H
#endif // SETTLERS_OF_CATAN_DEBUG_H

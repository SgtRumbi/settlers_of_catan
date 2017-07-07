#include "socatan_render.h"
#include "socatan_math.h"

#define DEFAULT_CIRCLE_SAMPLES 32

static void
DrawCircle(v2 Position, r32 Radius, u32 SampleCount = DEFAULT_CIRCLE_SAMPLES) {
    v2 Vertices2D[SampleCount];

    for(uint32 SampleIndex = 0;
        SampleIndex < SampleCount;
        ++SampleIndex) {
        Vertices2D[SampleIndex].X = Sin();
    }
}

void
RenderGame(game_state *GameState) {

}

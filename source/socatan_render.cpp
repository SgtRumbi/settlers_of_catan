#include "socatan_render.h"
#include "socatan_math.h"
#include "socatan_opengl.h"

void
RenderGame(memory_chunk *FrameMemory, game_state *GameState) {
    // TODO(js): Maybe other contexts?
    OpenGLRenderGame(FrameMemory, GameState);
}

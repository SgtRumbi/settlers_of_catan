#include "socatan_render.h"
#include "socatan_math.h"
#include "socatan_opengl.h"

#define DEFAULT_CIRCLE_SAMPLES 6

static void
CreateDefaultProgram(program *Result) {
    char *VertexShader = R"FOO(
in v2 Position;

void main(void) {
gl_Position = V4(P, 0.0f, 1.0f);
}
)FOO";

    char *FragmentShader = R"FOO(
out v4 Color;

void main(void) {
Color = V4(0.84f, 0.13f, 0.45f);
}
)FOO";

    GLuint Handle = CreateProgram(Result, GlobalHeaderCode, VertexShader, FragmentShader);

    Result->PositionID = glGetAttribLocation(Handle, "Position");
}

static void
DrawRectangle(v2 PStart, v2 PEnd, v4 Color) {
    glColor4fv(Color.E);
    glBegin(GL_TRIANGLES);

    glVertex2f(PStart.X, PStart.Y);
    glVertex2f(PEnd.X, PStart.Y);
    glVertex2f(PEnd.X, PEnd.Y);

    glVertex2f(PStart.X, PStart.Y);
    glVertex2f(PStart.X, PEnd.Y);
    glVertex2f(PEnd.X, PEnd.Y);

    glEnd();
}

// TODO(js): Make this work.
static void
DrawCircle(v2 P, r32 Radius, v4 Color, u32 SampleCount = DEFAULT_CIRCLE_SAMPLES) {
    v2 Vertices2D[SampleCount];

    for(uint32 SampleIndex = 0;
        SampleIndex < SampleCount;
        ++SampleIndex) {
        Vertices2D[SampleIndex].X = Radius*SinD((r32)SampleIndex / (r32)SampleCount);
        Vertices2D[SampleIndex].Y = Radius*CosD((r32)SampleIndex / (r32)SampleCount);
    }

    // TODO(js): Get rid of legacy
    glColor4fv(Color.E);

    glBegin(GL_POLYGON);

    // glVertex2f(Position.X, Position.Y);
    for(uint32 SampleIndex = 0;
        SampleIndex < SampleCount;
        ++SampleIndex) {
        v2 Vertex = Vertices2D[SampleIndex];
        // glVertex2f(SinD(2 * Pi32 * (r32)SampleIndex / (r32)SampleIndex), CosD(2 * Pi32 * (r32)SampleIndex / (r32)SampleIndex));
        glVertex2f(Vertex.X, Vertex.Y);
    }

    glEnd();
}

void
RenderGame(game_state *GameState) {
    static bool32 Initialized = false;
    static program DefaultProgram;
    if(!Initialized) {
        CreateDefaultProgram(&DefaultProgram);

        Initialized = true;
    }

    glClearColor(0.23f, 0.34f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawCircle(V2(0.0f, 0.0f), 1.0f, V4(0.15f, 0.46f, 0.16f, 1.0f));
    DrawRectangle(V2(0.0f, 0.0f), V2(0.6f, 0.3f), V4(0.46f, 0.15f, 0.16f, 1.0f));
}

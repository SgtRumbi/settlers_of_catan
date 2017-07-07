#include "socatan_render.h"
#include "socatan_math.h"

#define DEFAULT_CIRCLE_SAMPLES 32

static void
DrawCircle(v2 Position, r32 Radius, u32 SampleCount = DEFAULT_CIRCLE_SAMPLES) {
    v2 Vertices2D[SampleCount];

    for(uint32 SampleIndex = 0;
        SampleIndex < SampleCount;
        ++SampleIndex) {
        // Vertices2D[SampleIndex].X = Sin();
    }
}

void
RenderGame(game_state *GameState) {

}
#if 0
=======
#include "socatan_opengl.h"

#include <cstdio>

static void
DrawHexagon(real32 CenterX, real32 CenterY, real32 Radius) {
  real32 X1 = CenterX;
  real32 Y1 = CenterY - Radius;
   
}


void
RenderGame(game_state *Field) {
  static bool32 Initialized = false;
  static program Program;
  static GLuint BufferHandle = 1;
  if(!Initialized) {
    char *Header = R"FOO(
    #version 120
    
    #define v2 vec2
    #define v4 vec4
    #define V4 vec4
    )FOO";
    
    char *VertexShaderCode = R"FOO(
    in v2 Position;
        
    void main()  {
    gl_Position = Position;
    }
    )FOO";
    
    char *FragmentShaderCode = R"FOO(
    out v4 Color;
    
    void main() {
    Color = V4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    )FOO";
  
    GLuint ProgramHandle = CreateProgram(&Program, Header, VertexShaderCode, FragmentShaderCode);

    // glBindBuffer(GL_ARRAY_BUFFER, BufferHandle);
    // glBufferData(GL_ARRAY_BUFFER, 
  
    printf("Hier %s %d\n", __FILE__, __LINE__);
    Initialized = true;
  }

  glColor3f(1.0f, 0.0f, 0.0f);  
  glBegin(GL_TRIANGLES);
  
  glVertex2f(0.0f, 0.0f);
  glVertex2f(1.0f, 0.0f);
  glVertex2f(1.0f, 1.0f);
  
  glEnd();
}
#endif

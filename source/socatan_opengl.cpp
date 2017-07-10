#include "socatan_opengl.h"
#include "socatan_math.h"
#include "socatan_platform.h"

gl_buffer_data glBufferData;
gl_bind_buffer glBindBuffer;
gl_create_shader glCreateShader;
gl_shader_source glShaderSource;
gl_compile_shader glCompileShader;
gl_attach_shader glAttachShader;
gl_create_program glCreateProgram;
gl_link_program glLinkProgram;
gl_use_program glUseProgram;
gl_vertex_attrib_pointer glVertexAttribPointer;
gl_get_attrib_location glGetAttribLocation;
gl_enable_vertex_attrib_array glEnableVertexAttribArray;
gl_disable_vertex_attrib_array glDisableVertexAttribArray;
gl_bind_framebuffer glBindFramebuffer;
gl_framebuffer_texture glFramebufferTexture;
gl_get_shaderiv glGetShaderiv;
gl_get_shader_info_log glGetShaderInfoLog;

static void
LoadOpenGLFunctions() {
    const char *OpenGLExtensionsString = (const char *)glGetString(GL_EXTENSIONS);
    opengl_get_proc_address *LoadFunction = Platform.OpenGLGetProcAddressFunction;
    // PlatformLogInfo("OpenGL-Extensions: %s", OpenGLExtensionsString);

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_buffer_object")) {
        glBufferData = (gl_buffer_data)LoadFunction("glBufferData");
        glBindBuffer = (gl_bind_buffer)LoadFunction("glBindBuffer");
    } else {
        PlatformLogError("GL_ARB_vertex_buffer_object is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_shader_objects")) {
        glCreateShader = (gl_create_shader)LoadFunction("glCreateShader");
        glShaderSource = (gl_shader_source)LoadFunction("glShaderSource");
        glCompileShader = (gl_compile_shader)LoadFunction("glCompileShader");
        glCreateProgram = (gl_create_program)LoadFunction("glCreateProgram");
        glAttachShader = (gl_attach_shader)LoadFunction("glAttachShader");
        glLinkProgram = (gl_link_program)LoadFunction("glLinkProgram");
        glUseProgram = (gl_use_program)LoadFunction("glUseProgram");
        glGetShaderiv = (gl_get_shaderiv)LoadFunction("glGetShaderiv");
        glGetShaderInfoLog = (gl_get_shader_info_log)LoadFunction("glGetShaderInfoLog");
    } else {
        PlatformLogError("GL_ARB_shader_objects is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_program")) {
        glVertexAttribPointer = (gl_vertex_attrib_pointer)LoadFunction("glVertexAttribPointer");
    } else {
        PlatformLogError("GL_ARB_vertex_program is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_shader")) {
        glGetAttribLocation = (gl_get_attrib_location)LoadFunction("glGetAttribLocation");
        glEnableVertexAttribArray = (gl_enable_vertex_attrib_array)LoadFunction("glEnableVertexAttribArray");
        glDisableVertexAttribArray = (gl_disable_vertex_attrib_array)LoadFunction("glDisableVertexAttribArray");
    } else {
        PlatformLogError("GL_ARB_vertex_shader is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_framebuffer_object")) {
        glBindFramebuffer = (gl_bind_buffer)LoadFunction("glBindFramebuffer");
        glFramebufferTexture = (gl_framebuffer_texture)LoadFunction("glFramebufferTexture");
    } else {
        PlatformLogError("Failed to load extension GL_ARB_framebuffer_object.");
    }
}

static GLuint
CreateShader(GLenum Type, char *Header, char *Content) {
    GLuint Result = glCreateShader(Type);

    char *SourceStrings[2] = {Header, Content};

    glShaderSource(Result, 2, (const GLchar *const *)SourceStrings, 0);
    glCompileShader(Result);

    GLint Compiled = 0;
    glGetShaderiv(Result, GL_COMPILE_STATUS, &Compiled);
    if(!Compiled) {
        Result = 0;

        GLsizei LogLength = 1024;
        GLchar InfoLog[LogLength];
        glGetShaderInfoLog(Result, LogLength, &LogLength, InfoLog);
        PlatformLogError("Failed to compile shader. Log: \n%s", InfoLog);
    } else {
        PlatformLogInfo("Successfully compiled shader.");
    }

    return(Result);
}

static GLuint
CreateProgram(program *Program, char *SharedHeader, char *VertexShaderCode, char *FragmentShaderCode) {
    GLuint Result = 0;

    GLuint VertexShader = CreateShader(GL_VERTEX_SHADER, SharedHeader, VertexShaderCode);
    GLuint FragmentShader = CreateShader(GL_FRAGMENT_SHADER, SharedHeader, FragmentShaderCode);

    if(VertexShader && FragmentShader) {
        Result = glCreateProgram();

        glAttachShader(Result, VertexShader);
        glAttachShader(Result, FragmentShader);

        glLinkProgram(Result);
    }

    Program->Handle = Result;
    Program->Linked = true;

    return(Result);
}

static void
UseProgram(program *Program) {
    if(Program) {
        glUseProgram(Program->Handle);
    } else {
        glUseProgram(0);
    }
}

static void
BindTex(GLenum Slot, GLenum Target, GLuint Handle) {
    glActiveTexture(Slot);
    glBindTexture(Target, Handle);
}

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
OpenGLRenderGame(game_state *GameState) {
    static bool32 Initialized = false;
    static program DefaultProgram;
    static GLuint BufferID = 1;
    if(!Initialized) {
        LoadOpenGLFunctions();

        glBindBuffer(GL_ARRAY_BUFFER, BufferID);
        r32 Vertices[6] = {
                0.0f, 0.0f,
                1.0f, 0.0f,
                1.0f, 1.0f
        };
        glBufferData(GL_ARRAY_BUFFER, 6*sizeof(r32), Vertices, GL_STATIC_DRAW);

        CreateDefaultProgram(&DefaultProgram);

        Initialized = true;
    }

    glClearColor(0.23f, 0.34f, 0.45f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawCircle(V2(0.0f, 0.0f), 1.0f, V4(0.15f, 0.46f, 0.16f, 1.0f));
    DrawRectangle(V2(0.0f, 0.0f), V2(0.6f, 0.3f), V4(0.46f, 0.15f, 0.16f, 1.0f));

    UseProgram(&DefaultProgram);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

#include "socatan_opengl.h"
#include "socatan_math.h"
#include "socatan_platform.h"

#if !defined(GL_VERSION_1_3)
gl_active_texture *glActiveTexture;
#endif

gl_gen_buffers *glGenBuffers;
gl_buffer_data *glBufferData;
gl_bind_buffer *glBindBuffer;

gl_create_shader *glCreateShader;
gl_shader_source *glShaderSource;
gl_compile_shader *glCompileShader;
gl_attach_shader *glAttachShader;
gl_create_program *glCreateProgram;
gl_link_program *glLinkProgram;
gl_use_program *glUseProgram;
gl_vertex_attrib_pointer *glVertexAttribPointer;
gl_get_attrib_location *glGetAttribLocation;
gl_enable_vertex_attrib_array *glEnableVertexAttribArray;
gl_disable_vertex_attrib_array *glDisableVertexAttribArray;

gl_uniform1f *glUniform1f;
gl_uniform2f *glUniform2f;
gl_uniform3f *glUniform3f;
gl_uniform4f *glUniform4f;
gl_uniform1i *glUniform1i;
gl_uniform2i *glUniform2i;
gl_uniform3i *glUniform3i;
gl_uniform4i *glUniform4i;
gl_uniform1fv *glUniform1fv;
gl_uniform2fv *glUniform2fv;
gl_uniform3fv *glUniform3fv;
gl_uniform4fv *glUniform4fv;
gl_uniform1iv *glUniform1iv;
gl_uniform2iv *glUniform2iv;
gl_uniform3iv *glUniform3iv;
gl_uniform4iv *glUniform4iv;
// gl_uniform_matrix2fv glUniformMatrix2fv;
// gl_uniform_matrix3fv glUniformMatrix3fv;
gl_uniform_matrix4fv *glUniformMatrix4fv;

gl_bind_framebuffer *glBindFramebuffer;
gl_framebuffer_texture *glFramebufferTexture;
gl_get_shaderiv *glGetShaderiv;
gl_get_shader_info_log *glGetShaderInfoLog;

static void
LoadOpenGLFunctions() {
    const char *OpenGLExtensionsString = (const char *)glGetString(GL_EXTENSIONS);
    opengl_get_proc_address *LoadFunction = Platform.OpenGLGetProcAddressFunction;
    // PlatformLogInfo("OpenGL-Extensions: %s", OpenGLExtensionsString);

    // Active Texture should be available
#if !defined(GL_VERSION_1_3)
    glActiveTexture = (gl_active_texture)LoadFunction("glActiveTexture");
#endif

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_buffer_object")) {
        glGenBuffers = (gl_gen_buffers *)LoadFunction("glGenBuffers");
        glBufferData = (gl_buffer_data *)LoadFunction("glBufferData");
        glBindBuffer = (gl_bind_buffer *)LoadFunction("glBindBuffer");
    } else {
        PlatformLogError("GL_ARB_vertex_buffer_object is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_shader_objects")) {
        glCreateShader = (gl_create_shader *)LoadFunction("glCreateShader");
        glShaderSource = (gl_shader_source *)LoadFunction("glShaderSource");
        glCompileShader = (gl_compile_shader *)LoadFunction("glCompileShader");
        glCreateProgram = (gl_create_program *)LoadFunction("glCreateProgram");
        glAttachShader = (gl_attach_shader *)LoadFunction("glAttachShader");
        glLinkProgram = (gl_link_program *)LoadFunction("glLinkProgram");
        glUseProgram = (gl_use_program *)LoadFunction("glUseProgram");
        glGetShaderiv = (gl_get_shaderiv *)LoadFunction("glGetShaderiv");
        glGetShaderInfoLog = (gl_get_shader_info_log *)LoadFunction("glGetShaderInfoLog");

        glUniform1f = (gl_uniform1f *)LoadFunction("glUniform1f");
        glUniform2f = (gl_uniform2f *)LoadFunction("glUniform2f");
        glUniform3f = (gl_uniform3f *)LoadFunction("glUniform3f");
        glUniform4f = (gl_uniform4f *)LoadFunction("glUniform4f");
        glUniform1i = (gl_uniform1i *)LoadFunction("glUniform1i");
        glUniform2i = (gl_uniform2i *)LoadFunction("glUniform2i");
        glUniform3i = (gl_uniform3i *)LoadFunction("glUniform3i");
        glUniform4i = (gl_uniform4i *)LoadFunction("glUniform1i");

        glUniform1fv = (gl_uniform1fv *)LoadFunction("glUniform1fv");
        glUniform2fv = (gl_uniform2fv *)LoadFunction("glUniform2fv");
        glUniform3fv = (gl_uniform3fv *)LoadFunction("glUniform3fv");
        glUniform4fv = (gl_uniform4fv *)LoadFunction("glUniform4fv");
        glUniform1iv = (gl_uniform1iv *)LoadFunction("glUniform1iv");
        glUniform2iv = (gl_uniform2iv *)LoadFunction("glUniform2iv");
        glUniform3iv = (gl_uniform3iv *)LoadFunction("glUniform3iv");
        glUniform4iv = (gl_uniform4iv *)LoadFunction("glUniform1iv");

        // glUniformMatrix2fv = (gl_uniform_matrix2fv)LoadFunction("glUniformMatrix2fv");
        // glUniformMatrix3fv = (gl_uniform_matrix3fv)LoadFunction("glUniformMatrix3fv");
        glUniformMatrix4fv = (gl_uniform_matrix4fv *)LoadFunction("glUniformMatrix4fv");
    } else {
        PlatformLogError("GL_ARB_shader_objects is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_program")) {
        glVertexAttribPointer = (gl_vertex_attrib_pointer *)LoadFunction("glVertexAttribPointer");
    } else {
        PlatformLogError("GL_ARB_vertex_program is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_shader")) {
        glGetAttribLocation = (gl_get_attrib_location *)LoadFunction("glGetAttribLocation");
        glEnableVertexAttribArray = (gl_enable_vertex_attrib_array *)LoadFunction("glEnableVertexAttribArray");
        glDisableVertexAttribArray = (gl_disable_vertex_attrib_array *)LoadFunction("glDisableVertexAttribArray");
    } else {
        PlatformLogError("GL_ARB_vertex_shader is not supported.");
    }

    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_framebuffer_object")) {
        glBindFramebuffer = (gl_bind_buffer *)LoadFunction("glBindFramebuffer");
        glFramebufferTexture = (gl_framebuffer_texture *)LoadFunction("glFramebufferTexture");
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
    if(Compiled != GL_TRUE) {
        GLsizei LogLength = 0;
        GLchar InfoLog[1024];
        glGetShaderInfoLog(Result, 1024, &LogLength, InfoLog);
        PlatformLogError("Failed to compile shader. Log: \n%s", InfoLog);

        Result = 0;
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
in v2 P;

void main(void) {
gl_Position = V4(P, 0.0f, 1.0f);
}
)FOO";

    char *FragmentShader = R"FOO(
out v4 Color;

void main(void) {
Color = V4(0.84f, 0.13f, 0.45f, 1.0f);
}
)FOO";

    GLuint Handle = CreateProgram(Result, GlobalHeaderCode, VertexShader, FragmentShader);

    Result->PositionID = glGetAttribLocation(Handle, "P");
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

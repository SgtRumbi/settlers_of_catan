#include <GL/gl.h>
#include <cstdio>

#if !defined(SETTLERS_OF_CATAN_OPENGL_H)

typedef void (*gl_buffer_data)(GLenum, GLsizeiptr, const GLvoid *, GLenum);
typedef void (*gl_bind_buffer)(GLenum, uint32);
typedef uint32 (*gl_create_shader)(GLenum);
typedef void (*gl_shader_source)(uint32, GLsizei, const GLchar * const *, const GLint *);
typedef void (*gl_compile_shader)(uint32);
typedef uint32 (*gl_create_program)(void);
typedef void (*gl_attach_shader)(uint32, uint32);
typedef void (*gl_link_program)(uint32);
typedef void (*gl_use_program)(uint32);
typedef void (*gl_vertex_attrib_pointer)(uint32, int32, GLenum, GLboolean, GLsizei, const GLvoid *);
typedef int32 (*gl_get_attrib_location)(uint32, const char *);
typedef void (*gl_enable_vertex_attrib_array)(uint32);
typedef void (*gl_disable_vertex_attrib_array)(uint32);
typedef void (*gl_bind_framebuffer)(GLenum, uint32);
typedef void (*gl_framebuffer_texture)(GLenum, GLenum, uint32, int32);
typedef void (*gl_get_shaderiv)(uint32, GLenum, int32 *);
typedef void (*gl_get_shader_info_log)(uint32, GLsizei, GLsizei *, char *);

static gl_buffer_data glBufferData;
static gl_bind_buffer glBindBuffer;
static gl_create_shader glCreateShader;
static gl_shader_source glShaderSource;
static gl_compile_shader glCompileShader;
static gl_attach_shader glAttachShader;
static gl_create_program glCreateProgram;
static gl_link_program glLinkProgram;
static gl_use_program glUseProgram;
static gl_vertex_attrib_pointer glVertexAttribPointer;
static gl_get_attrib_location glGetAttribLocation;
static gl_enable_vertex_attrib_array glEnableVertexAttribArray;
static gl_disable_vertex_attrib_array glDisableVertexAttribArray;
static gl_bind_framebuffer glBindFramebuffer;
static gl_framebuffer_texture glFramebufferTexture;
static gl_get_shaderiv glGetShaderiv;
static gl_get_shader_info_log glGetShaderInfoLog;

struct program {
    GLuint Handle;
    GLboolean Linked;
};

inline GLuint
CreateShader(GLenum Type, char *Header, char *Content) {
    GLuint Result = glCreateShader(Type);

    char *SourceStrings[2] = {
      Header,
      Content
    };


    glShaderSource(Result, 2, SourceStrings, 0);
    glCompileShader(Result);

    return(Result);
}

inline GLuint
CreateProgram(program *Program, char *SharedHeader, char *VertexShaderCode, char *FragmentShaderCode) {
    GLuint Result;

    GLuint VertexShader = CreateShader(GL_VERTEX_SHADER, SharedHeader, VertexShaderCode);
    GLuint FragmentShader = CreateShader(GL_FRAGMENT_SHADER, SharedHeader, FragmentShaderCode);

    if(VertexShader && FragmentShader) {
        Result = glCreateProgram();

        glAttachShader(Result, VertexShader);
        glAttachShader(Result, FragmentShader);

        glLinkProgram(Result);
        // TODO(js): Error checks
    }

    Program->Handle = Result;
    Program->Linked = true;

    return(Result);
}

inline void
UseProgram(program *Program) {
    if(Program) {
        glUseProgram(Program->Handle);
    } else {
        glUseProgram(0);
    }
}

#define SETTLERS_OF_CATAN_OPENGL_H
#endif // SETTLERS_OF_CATAN_OPENGL_H


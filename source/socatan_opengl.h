#if !defined(SETTLERS_OF_CATAN_OPENGL_H)

#include <GL/gl.h>
#include <cstdio>
#include "socatan_types.h"
#include "socatan.h"

typedef void *opengl_get_proc_address(char *Name);

typedef void (*gl_buffer_data)(GLenum, GLsizeiptr, const GLvoid *, GLenum);
typedef void (*gl_bind_buffer)(GLenum, GLuint);
typedef GLuint (*gl_create_shader)(GLenum);
typedef void (*gl_shader_source)(GLuint, GLsizei, const GLchar * const *, const GLint *);
typedef void (*gl_compile_shader)(GLuint);
typedef GLuint (*gl_create_program)(void);
typedef void (*gl_attach_shader)(GLuint, GLuint);
typedef void (*gl_link_program)(GLuint);
typedef void (*gl_use_program)(GLuint);
typedef void (*gl_vertex_attrib_pointer)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *);
typedef GLint (*gl_get_attrib_location)(GLuint, const char *);
typedef void (*gl_enable_vertex_attrib_array)(GLuint);
typedef void (*gl_disable_vertex_attrib_array)(GLuint);
typedef void (*gl_bind_framebuffer)(GLenum, GLuint);
typedef void (*gl_framebuffer_texture)(GLenum, GLenum, GLuint, GLint);
typedef void (*gl_get_shaderiv)(GLuint, GLenum, GLint *);
typedef void (*gl_get_shader_info_log)(GLuint, GLsizei, GLsizei *, char *);

extern gl_buffer_data glBufferData;
extern gl_bind_buffer glBindBuffer;
extern gl_create_shader glCreateShader;
extern gl_shader_source glShaderSource;
extern gl_compile_shader glCompileShader;
extern gl_attach_shader glAttachShader;
extern gl_create_program glCreateProgram;
extern gl_link_program glLinkProgram;
extern gl_use_program glUseProgram;
extern gl_vertex_attrib_pointer glVertexAttribPointer;
extern gl_get_attrib_location glGetAttribLocation;
extern gl_enable_vertex_attrib_array glEnableVertexAttribArray;
extern gl_disable_vertex_attrib_array glDisableVertexAttribArray;
extern gl_bind_framebuffer glBindFramebuffer;
extern gl_framebuffer_texture glFramebufferTexture;
extern gl_get_shaderiv glGetShaderiv;
extern gl_get_shader_info_log glGetShaderInfoLog;

static char *GlobalHeaderCode = R"FOO(
#version 150

#define v2 vec2
#define v3 vec3
#define v4 vec4

#define V2 vec2
#define V3 vec3
#define V4 vec4

#define m4x4 mat4x4

#define f32 float
#define i32 int
)FOO";

struct program {
    GLuint Handle;
    int32 Linked;

    GLint PositionID;
};

void OpenGLRenderGame(game_state *GameState);

#define SETTLERS_OF_CATAN_OPENGL_H
#endif // SETTLERS_OF_CATAN_OPENGL_H

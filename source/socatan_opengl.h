#if !defined(SETTLERS_OF_CATAN_OPENGL_H)

#include <GL/gl.h>
#include <cstdio>
#include "socatan_types.h"
#include "socatan.h"

typedef void *opengl_get_proc_address(char *Name);

typedef void gl_active_texture(GLenum texture);
typedef void gl_gen_buffers(GLuint Amount, GLuint *Buffers);
typedef void gl_buffer_data(GLenum, GLsizeiptr, const GLvoid *, GLenum);
typedef void gl_bind_buffer(GLenum, GLuint);
typedef GLuint gl_create_shader(GLenum);
typedef void gl_shader_source(GLuint, GLsizei, const GLchar * const *, const GLint *);
typedef void gl_compile_shader(GLuint);
typedef GLuint gl_create_program(void);
typedef void gl_attach_shader(GLuint, GLuint);
typedef void gl_link_program(GLuint);
typedef void gl_use_program(GLuint);
typedef void gl_vertex_attrib_pointer(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *);
typedef GLint gl_get_attrib_location(GLuint, const char *);
typedef void gl_enable_vertex_attrib_array(GLuint);
typedef void gl_disable_vertex_attrib_array(GLuint);
typedef void gl_bind_framebuffer(GLenum, GLuint);
typedef void gl_framebuffer_texture(GLenum, GLenum, GLuint, GLint);
typedef void gl_get_shaderiv(GLuint, GLenum, GLint *);
typedef void gl_get_shader_info_log(GLuint, GLsizei, GLsizei *, char *);
typedef void gl_uniform1f(GLint location, GLfloat v0);
typedef void gl_uniform2f(GLint location, GLfloat v0, GLfloat v1);
typedef void gl_uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
typedef void gl_uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
typedef void gl_uniform1i(GLint location, GLint v0);
typedef void gl_uniform2i(GLint location, GLint v0, GLint v1);
typedef void gl_uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
typedef void gl_uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
typedef void gl_uniform1fv(GLint location, GLsizei count, const GLfloat *value);
typedef void gl_uniform2fv(GLint location, GLsizei count, const GLfloat *value);
typedef void gl_uniform3fv(GLint location, GLsizei count, const GLfloat *value);
typedef void gl_uniform4fv(GLint location, GLsizei count, const GLfloat *value);
typedef void gl_uniform1iv(GLint location, GLsizei count, const GLint *value);
typedef void gl_uniform2iv(GLint location, GLsizei count, const GLint *value);
typedef void gl_uniform3iv(GLint location, GLsizei count, const GLint *value);
typedef void gl_uniform4iv(GLint location, GLsizei count, const GLint *value);
typedef void gl_uniform_matrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void gl_uniform_matrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void gl_uniform_matrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);

// OpenGL 1.3
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_MULTISAMPLE                    0x809D

// Not present on win32.
#if !defined(GL_VERSION_1_3)
extern gl_active_texture *glActiveTexture;
#endif

// OpenGL 1.5
#define GL_ARRAY_BUFFER                   0x8892
#define GL_ELEMENT_ARRAY_BUFFER           0x8893

#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA

extern gl_gen_buffers *glGenBuffers;
extern gl_buffer_data *glBufferData;
extern gl_bind_buffer *glBindBuffer;

// OpenGL 2.0
#define GL_MAX_DRAW_BUFFERS               0x8824
#define GL_DRAW_BUFFER0                   0x8825
#define GL_DRAW_BUFFER1                   0x8826
#define GL_DRAW_BUFFER2                   0x8827
#define GL_DRAW_BUFFER3                   0x8828
#define GL_DRAW_BUFFER4                   0x8829
#define GL_DRAW_BUFFER5                   0x882A
#define GL_DRAW_BUFFER6                   0x882B
#define GL_DRAW_BUFFER7                   0x882C
#define GL_DRAW_BUFFER8                   0x882D
#define GL_DRAW_BUFFER9                   0x882E
#define GL_DRAW_BUFFER10                  0x882F
#define GL_DRAW_BUFFER11                  0x8830
#define GL_DRAW_BUFFER12                  0x8831
#define GL_DRAW_BUFFER13                  0x8832
#define GL_DRAW_BUFFER14                  0x8833
#define GL_DRAW_BUFFER15                  0x8834
#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_FRAGMENT_SHADER                0x8B30
#define GL_VERTEX_SHADER                  0x8B31

extern gl_create_shader *glCreateShader;
extern gl_shader_source *glShaderSource;
extern gl_compile_shader *glCompileShader;
extern gl_attach_shader *glAttachShader;
extern gl_create_program *glCreateProgram;
extern gl_link_program *glLinkProgram;
extern gl_use_program *glUseProgram;
extern gl_vertex_attrib_pointer *glVertexAttribPointer;
extern gl_get_attrib_location *glGetAttribLocation;
extern gl_get_shaderiv *glGetShaderiv;
extern gl_get_shader_info_log *glGetShaderInfoLog;

extern gl_uniform1f *glUniform1f;
extern gl_uniform2f *glUniform2f;
extern gl_uniform3f *glUniform3f;
extern gl_uniform4f *glUniform4f;
extern gl_uniform1i *glUniform1i;
extern gl_uniform2i *glUniform2i;
extern gl_uniform3i *glUniform3i;
extern gl_uniform4i *glUniform4i;
extern gl_uniform1fv *glUniform1fv;
extern gl_uniform2fv *glUniform2fv;
extern gl_uniform3fv *glUniform3fv;
extern gl_uniform4fv *glUniform4fv;
extern gl_uniform1iv *glUniform1iv;
extern gl_uniform2iv *glUniform2iv;
extern gl_uniform3iv *glUniform3iv;
extern gl_uniform4iv *glUniform4iv;
// TODO(js): Fix compilation error.
// extern gl_uniform_matrix2fv glUniformMatrix2fv;
// extern gl_uniform_matrix3fv glUniformMatrix3fv;
extern gl_uniform_matrix4fv *glUniformMatrix4fv;

// OpenGL 3.0
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9

extern gl_enable_vertex_attrib_array *glEnableVertexAttribArray;
extern gl_disable_vertex_attrib_array *glDisableVertexAttribArray;
extern gl_bind_framebuffer *glBindFramebuffer;
extern gl_framebuffer_texture *glFramebufferTexture;

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

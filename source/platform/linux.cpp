#include <cstdio>
#include <cstring>
#include <GL/gl.h>
#include <sys/mman.h>

#define PlatformLogInfo(...) LinuxLogInfo(__VA_ARGS__)
#define PlatformLogWarn(...) LinuxLogWarn(__VA_ARGS__)
#define PlatformLogError(...) LinuxLogError(__VA_ARGS__)

#define LinuxLogInfo(...) printf(__VA_ARGS__); printf("\n")
#define LinuxLogWarn(...) printf(__VA_ARGS__); printf("\n")
#define LinuxLogError(...) printf(__VA_ARGS__); printf("\n")

#include "platform.h"

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

// Above X11 bc defines... :/
#include "pfind.cpp"

#include <X11/Xlib.h>
#include <GL/glx.h>

typedef GLXContext (*glx_create_context_attribs_arb)(Display *, GLXFBConfig, GLXContext, Bool, const int *);

typedef int32 (*old_handler)(Display *, XErrorEvent *);
static bool32 GLXContextErrorOccurred = false;
static int32
GLXContextErrorHandler(Display *XDisplay, XErrorEvent *ErrorEvent) {
    GLXContextErrorOccurred = true;
    return(0);
}

static void
LinuxLogOpenGLContextInformation() {
    LinuxLogInfo("Loaded graphics driver %s (%s, by %s).\nShading Language Version: %s\nExtension: %s",
                 glGetString(GL_VERSION), glGetString(GL_RENDERER), glGetString(GL_VENDOR),
                 glGetString(GL_SHADING_LANGUAGE_VERSION), glGetString(GL_EXTENSIONS));
}

static void
LinuxInitializeAppMemory(app_memory *AppMemory, uint64 TransientMemorySize, uint64 PermanentMemorySize) {
    AppMemory->TransientMemorySize = TransientMemorySize;
    AppMemory->PermanentMemorySize = PermanentMemorySize;
    memory_index BasePointer = 0;
    uint64 TotalMemorySize = AppMemory->TransientMemorySize + AppMemory->PermanentMemorySize;
    AppMemory->PermanentMemory = mmap((void *)BasePointer, TotalMemorySize, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    AppMemory->TransientMemory = ((uint8 *)AppMemory->PermanentMemory + AppMemory->PermanentMemorySize);
}

int32
main(int32 argc, char *argv[]) {
    int32 WindowPositionX = 40;
    int32 WindowPositionY = 40;
    uint32 WindowDimensionX = 960;
    uint32 WindowDimensionY = 540;

    int32 BlueBits = 8;
    int32 GreenBits = 8;
    int32 RedBits = 8;
    // TODO(js): Do we need depth and alpha?
    int32 AlphaBits = 8;
    int32 DepthBits = 24;
    int32 StencilBits = 8;
    bool32 DoubleBuffered = true;

    int32 RequestedOpenGLVersionMajor = 3;
    int32 RequestedOpenGLVersionMinor = 0;

    int32 GLXVisualAttributes[] = {
            GLX_X_RENDERABLE, true,
            GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
            GLX_RENDER_TYPE, GLX_RGBA_BIT,
            GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
            GLX_RED_SIZE, RedBits,
            GLX_GREEN_SIZE, GreenBits,
            GLX_BLUE_SIZE, BlueBits,
            GLX_ALPHA_SIZE, AlphaBits,
            GLX_DEPTH_SIZE, DepthBits,
            GLX_STENCIL_SIZE, StencilBits,
            GLX_DOUBLEBUFFER, DoubleBuffered,
            0
    };

    Display *XDisplay = XOpenDisplay(NULL);

    if(XDisplay) {
        int32 GLXVersionMajor, GLXVersionMinor;
        if(!(!glXQueryVersion(XDisplay, &GLXVersionMajor, &GLXVersionMinor) ||
              ((GLXVersionMajor == 1) && (GLXVersionMinor < 3)) || (GLXVersionMajor < 1))) {
            int32 XScreen = DefaultScreen(XDisplay);

            int32 FrameBufferConfigsCount;
            GLXFBConfig *FrameBufferConfigs = glXChooseFBConfig(XDisplay, XScreen, GLXVisualAttributes,
                                                                &FrameBufferConfigsCount);
            if(FrameBufferConfigs) {
                int32 BestFrameBufferConfigurationIndex = -1;
                int32 WorstFrameBufferConfigurationIndex = -1;
                int32 BestSamplesCount = -1;
                // TODO(js): Change to something realistic
                int32 WorstSampleCount = 999;

                for(int32 FrameBufferConfigIndex = 0;
                    FrameBufferConfigIndex < FrameBufferConfigsCount;
                    ++FrameBufferConfigIndex) {
                    XVisualInfo *VisualInfo = glXGetVisualFromFBConfig(XDisplay,
                                                                       FrameBufferConfigs[FrameBufferConfigIndex]);
                    if(VisualInfo) {
                        int32 SampleBuffersCount;
                        int32 SampleCount;

                        glXGetFBConfigAttrib(XDisplay, FrameBufferConfigs[FrameBufferConfigIndex], GLX_SAMPLE_BUFFERS,
                                             &SampleBuffersCount);
                        glXGetFBConfigAttrib(XDisplay, FrameBufferConfigs[FrameBufferConfigIndex], GLX_SAMPLES,
                                             &SampleCount);

                        if((BestFrameBufferConfigurationIndex < 0) ||
                            SampleBuffersCount && (SampleCount > BestSamplesCount)) {
                            BestFrameBufferConfigurationIndex = FrameBufferConfigIndex;
                            BestSamplesCount = SampleCount;
                        }

                        if((WorstFrameBufferConfigurationIndex < 0) || (!SampleBuffersCount) ||
                            (SampleCount < WorstSampleCount)) {
                            WorstFrameBufferConfigurationIndex = FrameBufferConfigIndex;
                            WorstSampleCount = SampleCount;
                        }
                    }
                    XFree(VisualInfo);
                }

                GLXFBConfig BestFrameBufferConfiguration = FrameBufferConfigs[BestFrameBufferConfigurationIndex];

                XFree(FrameBufferConfigs);

                XVisualInfo *BestVisualInfo = glXGetVisualFromFBConfig(XDisplay, BestFrameBufferConfiguration);

                Colormap XColormap = XCreateColormap(XDisplay, RootWindow(XDisplay, BestVisualInfo->screen),
                                                     BestVisualInfo->visual, AllocNone);
                XSetWindowAttributes SetWindowAttributes;
                SetWindowAttributes.colormap = XColormap;
                SetWindowAttributes.background_pixel = 0;
                SetWindowAttributes.border_pixel = 0;
                SetWindowAttributes.event_mask = StructureNotifyMask;

                Window XWindow = XCreateWindow(XDisplay, RootWindow(XDisplay, XScreen), WindowPositionX,
                                               WindowPositionY, WindowDimensionX, WindowDimensionY, 0,
                                               BestVisualInfo->depth, InputOutput, BestVisualInfo->visual,
                                               CWBorderPixel | CWColormap | CWEventMask, &SetWindowAttributes);

                XFree(BestVisualInfo);

                XStoreName(XDisplay, XWindow, "OpenGL window");
                // TODO(js): Get rid of ExposureMask?
                // TODO(js): Add Mouse mask (or process input completely different)
                XSelectInput(XDisplay, XWindow, ExposureMask | KeyPressMask);
                XMapWindow(XDisplay, XWindow);

                const char *GLXExtensionsString = glXQueryExtensionsString(XDisplay, XScreen);

                glx_create_context_attribs_arb glXCreateContextAttribsARB =
                        (glx_create_context_attribs_arb)glXGetProcAddressARB((const GLubyte *)"glXCreateContextAttribsARB");

                GLXContext Context = 0;
                old_handler OldHandler = XSetErrorHandler(&GLXContextErrorHandler);

                if(IsExtensionSupported(GLXExtensionsString, "GLX_ARB_create_context") && glXCreateContextAttribsARB) {
                    int32 ContextAttributes[] = {
                            GLX_CONTEXT_MAJOR_VERSION_ARB, RequestedOpenGLVersionMajor,
                            GLX_CONTEXT_MINOR_VERSION_ARB, RequestedOpenGLVersionMinor,
                            0
                    };

                    Context = glXCreateContextAttribsARB(XDisplay, BestFrameBufferConfiguration, 0, true, ContextAttributes);

                    XSync(XDisplay, false);

                    if(GLXContextErrorOccurred && !Context) {
                        // If failed, create legacy context
                        ContextAttributes[1] = 1;
                        ContextAttributes[3] = 0;

                        Context = glXCreateContextAttribsARB(XDisplay, BestFrameBufferConfiguration, 0, true, ContextAttributes);
                    }
                } else {
                    // Use fallback to old context creation method
                    Context = glXCreateNewContext(XDisplay, BestFrameBufferConfiguration, GLX_RGBA_TYPE, 0, true);
                }

                XSync(XDisplay, false);
                XSetErrorHandler(OldHandler);

                if(!GLXContextErrorOccurred && Context) {
                    // TODO(js): Remove
                    if(glXIsDirect(XDisplay, Context)) {
                        PlatformLogInfo("Created direct OpenGL context.");
                    } else {
                        PlatformLogInfo("Created indirect OpenGL context.");
                    }

                    glXMakeCurrent(XDisplay, XWindow, Context);

                    LinuxLogOpenGLContextInformation();

                    const char *OpenGLExtensionsString = (const char *)glGetString(GL_EXTENSIONS);
                    // PlatformLogInfo("OpenGL-Extensions: %s", OpenGLExtensionsString);

                    bool32 ModernContextSupported = true;

                    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_buffer_object")) {
                        glBufferData = (gl_buffer_data)glXGetProcAddress((const GLubyte *)"glBufferData");
                        glBindBuffer = (gl_bind_buffer)glXGetProcAddress((const GLubyte *)"glBindBuffer");
                    } else {
                        ModernContextSupported = false;
                        PlatformLogError("GL_ARB_vertex_buffer_object is not supported.");
                    }

                    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_shader_objects")) {
                        glCreateShader = (gl_create_shader)glXGetProcAddress((const GLubyte *)"glCreateShader");
                        glShaderSource = (gl_shader_source)glXGetProcAddress((const GLubyte *)"glShaderSource");
                        glCompileShader = (gl_compile_shader)glXGetProcAddress((const GLubyte *)"glCompileShader");
                        glCreateProgram = (gl_create_program)glXGetProcAddress((const GLubyte *)"glCreateProgram");
                        glAttachShader = (gl_attach_shader)glXGetProcAddress((const GLubyte *)"glAttachShader");
                        glLinkProgram = (gl_link_program)glXGetProcAddress((const GLubyte *)"glLinkProgram");
                        glUseProgram = (gl_use_program)glXGetProcAddressARB((const GLubyte *)"glUseProgram");
                        glGetShaderiv = (gl_get_shaderiv)glXGetProcAddressARB((const GLubyte *)"glGetShaderiv");
                        glGetShaderInfoLog = (gl_get_shader_info_log)glXGetProcAddressARB((const GLubyte *)"glGetShaderInfoLog");
                    } else {
                        ModernContextSupported = false;
                        PlatformLogError("GL_ARB_shader_objects is not supported.");
                    }

                    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_program")) {
                        glVertexAttribPointer = (gl_vertex_attrib_pointer)glXGetProcAddressARB((const GLubyte *)"glVertexAttribPointer");
                    } else {
                        ModernContextSupported = false;
                        PlatformLogError("GL_ARB_vertex_program is not supported.");
                    }

                    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_vertex_shader")) {
                        glGetAttribLocation = (gl_get_attrib_location)glXGetProcAddressARB((const GLubyte *)"glGetAttribLocation");
                        glEnableVertexAttribArray = (gl_enable_vertex_attrib_array)glXGetProcAddressARB((const GLubyte *)"glEnableVertexAttribArray");
                        glDisableVertexAttribArray = (gl_disable_vertex_attrib_array)glXGetProcAddressARB((const GLubyte *)"glDisableVertexAttribArray");
                    } else {
                        ModernContextSupported = false;
                        PlatformLogError("GL_ARB_vertex_shader is not supported.");
                    }

                    bool32 SupportsFrameBufferObjects = false;
                    if(IsExtensionSupported(OpenGLExtensionsString, "GL_ARB_framebuffer_object")) {
                        SupportsFrameBufferObjects = true;

                        glBindFramebuffer = (gl_bind_buffer)glXGetProcAddressARB((const GLubyte *)"glBindFramebuffer");
                        glFramebufferTexture = (gl_framebuffer_texture)glXGetProcAddressARB((const GLubyte *)"glFramebufferTexture");
                    }

                    if(XWindow) {
                        app_memory AppMemory;
                        LinuxInitializeAppMemory(&AppMemory, Gigabytes(2), Megabytes(32));

                        XEvent CurrentXEvent;
                        bool32 Running = true;
                        bool32 ShouldUseModernOpenGL = false;
                        bool32 UseModernOpenGL = (ModernContextSupported && ShouldUseModernOpenGL);

                        loop_call LoopCallInfo = {};
                        LoopCallInfo.RenderConfiguration = UseModernOpenGL ?
                                                           LoopCallRenderConfiguration_HardwareAcceleratedModern :
                                                           LoopCallRenderConfiguration_HardwareAcceleratedLegacy;
                        LoopCallInfo.HardwareContextInformation.HardwareAcceleratedContextInitialized = true;
                        LoopCallInfo.HardwareContextInformation.SupportsFrameBufferObjects = SupportsFrameBufferObjects;
                        LoopCallInfo.HardwareContextInformation.EmbeddedOpenGL = false;
                        // TODO(js): Query/Make un-hardcoded... :)
                        LoopCallInfo.HardwareContextInformation.OpenGLMajorVersion = 3;
                        LoopCallInfo.HardwareContextInformation.OpenGLMajorVersion = 0;
                        LoopCallInfo.HardwareContextInformation.ModernContext = UseModernOpenGL;
                        LoopCallInfo.AppMemory = AppMemory;

                        XWindowAttributes WindowAttributes;

                        while(Running) {
                            XNextEvent(XDisplay, &CurrentXEvent);
                            switch(CurrentXEvent.type) {
                                case Expose: {
                                    // TODO(js): Draw is save requested!
                                } break;

                                case KeyPress: {
                                    Running = false;
                                } break;

                                InvalidDefaultCase;
                            }

                            XGetWindowAttributes(XDisplay, XWindow, &WindowAttributes);

                            LoopCallInfo.WindowWidth = WindowAttributes.width;
                            LoopCallInfo.WindowHeight = WindowAttributes.height;

                            LoopCall(&LoopCallInfo);

                            glXSwapBuffers(XDisplay, XWindow);
                        }
                    } else {
                        PlatformLogError("Failed to create X11-Window.");
                    }
                } else {
                    PlatformLogError("Failed to create OpenGL context.");
                }
            } else {
                PlatformLogError("Failed to get frame buffer configs.");
            }
        } else {
            PlatformLogError("Invalid GLX-version. (%d.%d)", GLXVersionMajor, GLXVersionMinor);
        }
    } else {
        PlatformLogError("Failed to open X11-Display.");
    }

    return(0);
}

    Contact GitHub API Training Shop Blog About 

    © 2017 GitHub, Inc. Terms Privacy Security Status Help 



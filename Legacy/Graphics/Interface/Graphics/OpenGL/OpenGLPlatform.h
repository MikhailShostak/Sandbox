#include <APlatform.h>

#if APlatformApple
    #include <OpenGL/gl.h>
#elif APlatformWindowsDesktop
    //#define GLEW_STATIC

extern "C"
{
    #include "GL/glew.h"
}

#else
    #error "Unsupported platform"
#endif

#include <iostream>
using namespace std;
#if !defined(_WIN32)
#include <unistd.h>
#endif

#if    defined(__APPLE__)

# include <GLUT/glut.h>
# include <OpenGL/gl.h>

#elif defined(_WIN32)

# include <GL/freeglut.h>
# define GL_GLEXT_PROTOTYPES
# include <GL/gl.h>
# if 1
# include "GL/glext.h"
# endif

#elif defined(__linux__)

# include <GL/glut.h>
# define GL_GLEXT_PROTOTYPES
# include <GL/gl.h>

#endif

#ifdef WORK_AROUND_FORCE_PTHREADS_INCLUSION
#include <pthread.h>
#endif

#include "check_gl.h"

int main(int argc, char *argv[])
{
    const GLubyte *msg;
    int major, minor;
#ifndef _WIN32
    char hostname[128];
#endif
#ifdef WORK_AROUND_FORCE_PTHREADS_INCLUSION
    pthread_getconcurrency();
#endif

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow(argv[0]);

    cout << "      host name: ";
#ifdef _WIN32
    cout << "(indeterminate)" << endl;
#else
    gethostname(hostname, sizeof(hostname));
    cout << hostname << endl;
#endif

    CHECK_GL(msg = glGetString(GL_VERSION));
    cout << " OpenGL version: " << msg << endl;

#if defined(_WIN32) && !defined(__MINGW32__)
    sscanf_s((char *) msg, "%d.%d", &major, &minor);
#else
    sscanf((char *) msg, "%d.%d", &major, &minor);
#endif

    CHECK_GL(msg = glGetString(GL_VENDOR));
    cout << "  OpenGL vendor: " << msg << endl;

    CHECK_GL(msg = glGetString(GL_RENDERER));
    cout << "OpenGL renderer: " << msg << endl;

    if (major >= 2) {
        cout << "   GLSL version: ";
#ifdef GL_SHADING_LANGUAGE_VERSION
        CHECK_GL(msg = glGetString(GL_SHADING_LANGUAGE_VERSION));
        cout << msg << endl;
#else
        cout << "(indeterminate)" << endl;
#endif
    } else
        cout << "   GLSL version: pre-1.10.59 (OpenGL is pre-2.0)" << endl;

#if 0 // if we need extensions...
# if 1 // pre OpenGL3.0
    msg = glGetString(GL_EXTENSIONS);
    cout << "extensions: " << msg << endl;
# else // post OpenGL3.0 (may contain bugs)
    int nExtn;
    CHECK_GL(glGetIntegerv(GL_NUM_EXTENSIONS, &nExtn));
    for (int i = 0; i < nExtn; i++) {
        msg = glGetStringi(GL_EXTENSIONS, i);
        cout << "extension " << i << ": " << msg << endl;
    }
# endif
#endif
}

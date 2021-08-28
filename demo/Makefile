PROGRAM = opengl_status

# UNAME is defined as the output of the "uname" in upper case, but
# under MinGW it's kind of lengthy and includes version information,
# which is not our intent, so let's trim it to "MINGW32" and hope for
# broad compatibility.
UNAME = $(shell uname | sed 's/_.*//' | tr a-z A-Z)

# Where GLUT's "GL" directory containing header files resides on Windows.
WINDOWS_GLUT_INCLUDE_DIR = ../../include

# Where GLUT's (DLL) library resides on Windows.
WINDOWS_GLUT_LIB_DIR     = ../../lib

CXX_FLAGS = -c -g -Wall $(CXX_FLAGS_$(UNAME))
CXX_FLAGS_LINUX = -DWORK_AROUND_FORCE_PTHREADS_INCLUSION
CXX_FLAGS_MINGW32 = -I$(WINDOWS_GLUT_INCLUDE_DIR)
CXX_FLAGS_DARWIN =

HDRS = \
	check_gl.h \
	wrap_gl_inclusion.h

LD_FLAGS = -g

LD_LIBS = $(LD_LIBS_$(UNAME))

# We need to include -pthread as part of
# WORK_AROUND_FORCE_PTHREADS_INCLUSION. (See "work_arounds.h").
LD_LIBS_LINUX = -pthread -lglut -lGL -lGLU

LD_LIBS_DARWIN = -framework GLUT -framework OpenGL
LD_LIBS_MINGW32 = -L$(WINDOWS_GLUT_LIB_DIR) -lfreeglut -lopengl32 -lglu32

.PHONY: default
default: $(PROGRAM)

.PHONY: NMakefile
NMakefile:
	make_nmakefile -o $@

.PHONY: clean
clean:
	rm -f *.o *.E *~

.PHONY: immaculate
immaculate: clean
	rm -rf $(PROGRAM) $(PROGRAM).dSYM/ opengl_status.tgz

.PHONY: tarball
tarball: opengl_status.tgz

$(PROGRAM): opengl_status.o
	g++ $(LD_FLAGS) $< -o $@ $(LD_LIBS)

opengl_status.o: opengl_status.cpp $(HDRS)
	g++ $(CXX_FLAGS) $<

opengl_status.E: opengl_status.cpp
	g++ -E -I$(WINDOWS_GLUT_INCLUDE_DIR) $< >$@

opengl_status.tgz: Makefile opengl_status.cpp $(HDRS)
	tar --dereference -czf $@ $^

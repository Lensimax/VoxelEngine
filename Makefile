#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need GLFW (http://www.glfw.org):
# Linux:
#   apt-get install libglfw-dev
# Mac OS X:
#   brew install glfw
# MSYS2:
#   pacman -S --noconfirm --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-glfw
#

# https://ubuntuforums.org/showthread.php?t=1204739

#CXX = g++
#CXX = clang++

EXE = green-engine
SOURCES = mainRenderer.cpp shader.cpp material/lambertian.cpp engineObject.cpp scene.cpp
SOURCES += models/transform.cpp models/drawableObject.cpp models/sphereMesh.cpp models/sphere.cpp models/meshLoader.cpp models/meshObject.cpp models/mesh.cpp
SOURCES += tools/camera.cpp tools/cameraProj.cpp tools/lights/directionnalLight.cpp

SOURCES += impl/imgui_impl_glfw.cpp impl/imgui_impl_opengl3.cpp
SOURCES += imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp


SOURCES += main.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))
UNAME_S := $(shell uname -s)

SourceDir=src/
ObjectDir=obj/
BinDir=bin/



##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

# mkdir -p build

## Using OpenGL loader: gl3w [default]
SOURCES += libs/gl3w/GL/gl3w.c
CXXFLAGS = -I$(SourceDir)libs/gl3w

CSources=$(addprefix $(SourceDir),$(SOURCES))
CObjects=$(addprefix $(ObjectDir),$(OBJS))
Executable=$(addprefix $(BinDir),$(EXE))

## Using OpenGL loader: glew
## (This assumes a system-wide installation)
# CXXFLAGS = -lGLEW -DIMGUI_IMPL_OPENGL_LOADER_GLEW

## Using OpenGL loader: glad
## (You'll also need to change the rule at line ~77 of this Makefile to compile/link glad.c/.o)
# SOURCES += ../libs/glad/src/glad.c
# CXXFLAGS = -I../libs/glad/include -DIMGUI_IMPL_OPENGL_LOADER_GLAD

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------

ifeq ($(UNAME_S), Linux) #LINUX
	ECHO_MESSAGE = "Linux"
	LIBS = -lGL `pkg-config --static --libs glfw3`

	CXXFLAGS += -I$(SourceDir)impl/ -I$(SourceDir)imgui/  `pkg-config --cflags glfw3`
	CXXFLAGS += -Wall -Wformat
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	#LIBS += -L/usr/local/lib -lglfw3
	LIBS += -L/usr/local/lib -lglfw

	CXXFLAGS += -I$(SourceDir)impl/ -I$(SourceDir)$(SourceDir)imgui/ -I/usr/local/include
	CXXFLAGS += -Wall -Wformat
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
   ECHO_MESSAGE = "Windows"
   LIBS = -lglfw3 -lgdi32 -lopengl32 -limm32

   CXXFLAGS += -I$(SourceDir)impl/ -I$(SourceDir)imgui/ `pkg-config --cflags glfw3`
   CXXFLAGS += -Wall -Wformat
   CFLAGS = $(CXXFLAGS)
endif

##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(ObjectDir)%.o:$(SourceDir)%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ObjectDir)%.o:$(SourceDir)models/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ObjectDir)%.o:$(SourceDir)material/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ObjectDir)%.o:$(SourceDir)tools/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ObjectDir)%.o:$(SourceDir)tools/lights/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ObjectDir)%.o:$(SourceDir)impl/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(ObjectDir)%.o:$(SourceDir)imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(ObjectDir)%.o:$(SourceDir)libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(Executable) $(CSources)
	@echo Build complete for $(ECHO_MESSAGE)

$(Executable): $(CObjects) #$(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

exec: $(Executable)
	optirun $(Executable)

clean:
	rm -f $(ObjectDir)*.o

superclean:
	make clean
	rm -f bin/*

install:
	mkdir bin;
	mkdir obj;

cleanImGui:
	rm -r imgui.ini

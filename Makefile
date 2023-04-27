# Classic g++
# CXX = g++
# Better error messages + faster compile times
CXX = clang++

# Executable name (target)
EXE = clothSimulation

# Compiler flags
CXXFLAGS = -std=c++17 -Wall
CXXFLAGS += -g -O2

# Debug segfaults
# CXXFLAGS += -fsanitize=address
# LDLIBS += -fsanitize=address

# Source files to compile
APP_DIR = src/app
APP = main.cpp buffer.cpp window.cpp openglrenderer.cpp vertexarray.cpp shaderprogram.cpp framebuffer.cpp camera.cpp
SOURCES = $(addprefix $(APP_DIR)/, $(APP))
CXXFLAGS += -Iinclude -I$(APP_DIR)

# Common (backend)
COMMON_DIR = src/common
COMMON = vector3d.cpp masse.cpp spring.cpp integrator.cpp cloth.cpp system.cpp util.cpp
SOURCES += $(addprefix $(COMMON_DIR)/, $(COMMON))
CXXFLAGS += -Isrc

# Dear ImGui source files
IMGUI_DIR = include/imgui
IMGUI = imgui.cpp imgui_demo.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp
IMGUI += imgui_impl_glfw.cpp imgui_impl_opengl3.cpp
SOURCES += $(addprefix $(IMGUI_DIR)/, $(IMGUI))
CXXFLAGS += -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

# All object files to make
OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

# Manual libs (because glfw is not installed on the VM...)
# A pre-compiled version of GLFW can be found in GLFW/libglfw3.a
LIBS += -Linclude/GLFW -lGL -lGLEW -lglfw3 -lX11 -lXrandr -lpthread -lXi -ldl -lXinerama -lXcursor

# Tell make where to look for files
# vpath %.h src/include
vpath % bin
vpath %.cpp $(APP_DIR) $(COMMON_DIR) $(IMGUI_DIR) $(IMGUI_DIR)/backends
vpath %.o build

# Build
%.o: %.cpp
	@echo "[CXX] Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o build/$@ $<

# Link
$(EXE): $(OBJS)
	@echo "[LD] Linking $(EXE)"
	@$(CXX) -o bin/$@ $(addprefix build/, $(notdir $^)) $(CXXFLAGS) $(LIBS)

.PHONY: all run dir clean mrpropre
all: dir $(EXE)
	@echo "[DONE] Build complete for $(EXE)"

run: all
	@echo "[MAKE] Launching program"
	@bin/$(EXE)

dir:
	@echo "[MAKE] Creating build directories"
	@mkdir -p build bin/tests bin/exercices

clean:
	@echo "[MAKE] Deleting object files and executables"
	@rm -f bin/$(EXE) $(addprefix build/, $(OBJS))

# Pour le rigolo
clena: cowsay_CLENA clean

mrpropre: clean

.PHONY: cowsay_%
cowsay_%:
	@echo " -------"
	@echo "| $(*F) |"
	@echo " -------"
	@echo "        \\   ^__^"
	@echo "         \\  (oo)\\_______"
	@echo "            (__)\\       )\\/\\"
	@echo "                ||----w |"
	@echo "                ||     ||"
	@echo

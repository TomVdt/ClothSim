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
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CXXFLAGS += -DDEBUG -fsanitize=address
endif

# Keyboard layout
LAYOUT ?= QWERTY
CXXFLAGS += -D$(LAYOUT)

# Source files to compile
APP_DIR = src/app
APP = main.cpp buffer.cpp window.cpp openglrenderer.cpp vertexarray.cpp shaderprogram.cpp camera.cpp
SOURCES = $(addprefix $(APP_DIR)/, $(APP))
CXXFLAGS += -Iinclude -I$(APP_DIR)

# Common (backend)
COMMON_DIR = src/common
COMMON = vector3d.cpp masse.cpp spring.cpp integrator.cpp cloth.cpp system.cpp util.cpp textrenderer.cpp chaincloth.cpp rectcloth.cpp diskcloth.cpp compositecloth.cpp constraint.cpp
SOURCES += $(addprefix $(COMMON_DIR)/, $(COMMON))
CXXFLAGS += -Isrc

# Tests
TESTS_DIR = src/test
TESTS = testVector3d testMasse testSpring testIntegrator1 testIntegrator2 testIntegrator3 testIntegrator4 testCloth1 testCloth2 testSystem testConstraint1 testConstraint2 testChainCloth testRectCloth testDiskCloth testCompositeCloth

# Exercices
EXERCICES_DIR = src/exercices
EXERCICES = exerciceP9 exerciceP10

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
vpath %.h src/include src/app/include
vpath % bin bin/tests bin/exercices
vpath %.cpp \
	$(APP_DIR) \
	$(COMMON_DIR) \
	$(IMGUI_DIR) \
	$(IMGUI_DIR)/backends \
	$(EXERCICES_DIR)/P9 \
	$(EXERCICES_DIR)/P10 \
	$(TESTS_DIR)
vpath %.o build

# Build
%.o: %.cpp
	@echo "[CXX] Compiling $<"
	@$(CXX) $(CXXFLAGS) -c -o build/$@ $<

# Link
$(EXE): $(OBJS)
	@echo "[LD] Linking $(EXE)"
	@$(CXX) -o bin/$@ $(addprefix build/, $(notdir $^)) $(CXXFLAGS) $(LIBS)

# Tests
test%: test%.o $(addsuffix .o, $(basename $(notdir $(COMMON))))
	@echo "[LD] Linking $@"
	@$(CXX) -o bin/tests/$@ $(addprefix build/, $(notdir $^)) $(CXXFLAGS) $(LIBS)

# Exercices
exerciceP%: exerciceP%.o $(addsuffix .o, $(basename $(notdir $(COMMON))))
	@echo "[LD] Linking $@"
	@$(CXX) -o bin/exercices/$@ $(addprefix build/, $(notdir $^)) $(CXXFLAGS) $(LIBS)

# General tasks
.PHONY: all tests run dir docs clean clean_app clean_common clean_imgui clena mrpropre
all: dir $(EXE) tests exercices docs
	@echo "[DONE] Build complete for $(EXE)"

tests: dir $(TESTS)
	@echo "[MAKE] Build complete for tests"

exercices: $(EXERCICES)
	@echo "[MAKE] Build complete for exercices"

run: dir $(EXE)
	@echo "[MAKE] Launching program"
	@bin/$(EXE)

run_tests: tests
	@for i in bin/tests/*; \
		do echo "[TEST] Running $$i"; \
		$$i; \
		done

dir:
	@echo "[MAKE] Creating build directories"
	@mkdir -p build bin/tests bin/exercices

docs:
	@echo "[DOXYGEN] Generating documentation"
	@doxygen > /dev/null 2>&1

open_docs: docs
	@echo "[MAKE] Opening documentation"
	@xdg-open doxydocs/html/index.html

clean:
	@echo "[MAKE] Deleting object files and executables"
	@rm -f build/*.o bin/$(EXE) bin/tests/* bin/exercices/*

clean_common:
	@echo "[MAKE] Deleting object files for common"
	@rm $(addprefix build/, $(COMMON:.cpp=.o))

clean_app:
	@echo "[MAKE] Deleting object files for app"
	@rm $(addprefix build/, $(APP:.cpp=.o))

clean_imgui:
	@echo "[MAKE] Deleting object files for imgui"
	@rm $(addprefix build/, $(IMGUI:.cpp=.o))

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

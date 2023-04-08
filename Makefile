CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++17 -Wall

# Debug
# CXXFLAGS += -g
# Optimisation
CXXFLAGS += -O2
# Où chercher les .h
CXXFLAGS += -I src

# Où chercher les fichiers source
# https://makefiletutorial.com/#the-vpath-directive

vpath %.h src/include
vpath %.cpp src src/test
vpath %.o build

# Tout compiler et linker

.PHONY: all dir clean
all: dir test

test: dir \
	bin/tests/testVector3d \
	bin/tests/testSpring \
	bin/tests/testMasse \
	bin/tests/testIntegrator1 \
	bin/tests/testIntegrator2 \
	bin/tests/testIntegrator3 \
	bin/tests/testIntegrator4 \
	bin/tests/testTissu1 \
	bin/tests/testTissu2

# Compilation
# ne surtout pas avoir 2 fichiers de même nom...

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o build/$@

# Linking tests

bin/tests/testVector3d: testVector3d.o vector3d.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testSpring: testSpring.o spring.o vector3d.o masse.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testMasse: testMasse.o spring.o vector3d.o masse.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testIntegrator1: testIntegrator1.o integrator.o vector3d.o masse.o spring.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testIntegrator2: testIntegrator2.o integrator.o vector3d.o masse.o spring.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testIntegrator3: testIntegrator3.o integrator.o vector3d.o masse.o spring.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testIntegrator4: testIntegrator4.o integrator.o vector3d.o masse.o spring.o constants.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testTissu1: testTissu1.o integrator.o vector3d.o masse.o spring.o constants.o tissu.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@

bin/tests/testTissu2: testTissu2.o integrator.o vector3d.o masse.o spring.o constants.o tissu.o
	$(CXX) $(CXXFLAGS) $(addprefix build/, $(notdir $^)) -o $@


# Executer un test précis
# Ex: `make run_testIntegrator1`

run_test%: bin/tests/test%
	@bin/tests/test$*

# Créer les dossiers necessaires à la compilation (éviter de mettre des .o partout)

dir:
	@echo Creating necessary directories...
	@mkdir -p build bin bin/tests

# Supprime les résultats de compilation précédents

clean:
	@echo Removing compiled object files...
	@rm -r build
	@echo Removing executables...
	@rm -r bin

clena: cowsay_CLENA clean

.PHONY: cowsay_% clean
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

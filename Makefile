# WARNING: if you are on windows, you need to have g++ installed with MinGW

CXX = g++
CXXFLAGS += -I./include
# CXXFLAGS += -v
LDFLAGS += -L./lib -nostdlib

# Automatically find all .cpp files in the src/ directory
SRC = $(wildcard src/*.cpp)
OUT = simple_bezier
EXT =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    LIBS = -L./lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
ifeq ($(UNAME_S), Darwin)
    LIBS = -L./lib -lraylib -framework OpenGL
endif
# Windows platform; assumes MinGW
ifeq ($(OS), Windows_NT)
    LIBS = -L./lib -lraylib -lopengl32 -lgdi32
    EXT = .exe
endif

# Build target
$(OUT)$(EXT): $(SRC)
	$(CXX) $(SRC) -o $(OUT)$(EXT) $(CXXFLAGS) $(LIBS)

# Clean target
clean:
	rm -f $(OUT)$(EXT)

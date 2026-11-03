# Makefile para Super Monkey Marble 3D
# Compatible con Linux, Windows (MinGW/w64devkit) y macOS

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

ifeq ($(OS),Windows_NT)
    TARGET = marble_runner.exe
    LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
    RM = del /Q /S
else
    UNAME_S := $(shell uname -s)
    TARGET = marble_runner
    ifeq ($(UNAME_S),Linux)
        LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    endif
    ifeq ($(UNAME_S),Darwin)
        LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
    endif
    RM = rm -f
endif

# Búsqueda de todos los archivos .cpp en src/ y subdirectorios
SRCS = src/main.cpp \
       src/core/GameManager.cpp \
       src/entities/Marble.cpp \
       src/entities/Platform.cpp \
       src/entities/Coin.cpp \
       src/entities/Goal.cpp \
       src/levels/Level.cpp \
       src/levels/Level1.cpp \
       src/levels/Level2.cpp \
       src/levels/Level3.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	@echo "=========================================="
	@echo " Compilación exitosa: ./$(TARGET)"
	@echo "=========================================="

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET)

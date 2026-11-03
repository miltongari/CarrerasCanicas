#!/usr/bin/env bash
set -e

echo "Compilando Super Monkey Marble 3D (Arquitectura Modular)..."

g++ -std=c++17 -Wall -Wextra -O2 -Iinclude \
    src/main.cpp \
    src/core/GameManager.cpp \
    src/entities/Marble.cpp \
    src/entities/Platform.cpp \
    src/entities/Coin.cpp \
    src/entities/Goal.cpp \
    src/levels/Level.cpp \
    src/levels/Level1.cpp \
    src/levels/Level2.cpp \
    src/levels/Level3.cpp \
    -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
    -o marble_runner

echo "¡Compilación terminada con éxito!"
echo "Ejecuta el juego con: ./marble_runner"

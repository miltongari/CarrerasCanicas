@echo off
setlocal

:: Solución para rutas UNC (\\wsl.localhost) en Windows
pushd "%~dp0"

echo =======================================================
echo   Compilando Super Monkey Marble 3D (Arquitectura Modular)
echo =======================================================

g++ -std=c++17 -Wall -Wextra -O2 -Iinclude ^
    src/main.cpp ^
    src/core/GameManager.cpp ^
    src/entities/Marble.cpp ^
    src/entities/Platform.cpp ^
    src/entities/Coin.cpp ^
    src/entities/Goal.cpp ^
    src/levels/Level.cpp ^
    src/levels/Level1.cpp ^
    src/levels/Level2.cpp ^
    src/levels/Level3.cpp ^
    -lraylib -lopengl32 -lgdi32 -lwinmm ^
    -o marble_runner.exe

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] La compilacion ha fallado. Revisa MinGW y Raylib.
    popd
    pause
    exit /b %errorlevel%
)

echo.
echo [EXITO] Compilacion completada con exito.
echo Ejecuta escribiendo: marble_runner.exe
echo.
popd
pause

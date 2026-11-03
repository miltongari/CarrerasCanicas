# ⚪ Marble Runner 3D

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Raylib](https://img.shields.io/badge/Raylib-5.0%2B-white?style=for-the-badge&logo=raylib&logoColor=black)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20WSL-blueviolet?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

**Un videojuego 3D de plataformas y precisión de alta dificultad inspirado en clásicos como *Super Monkey Ball* y *Marble Blast Ultra*, desarrollado en C++17 utilizando Raylib y OpenGL.**

[Características](#-características) • [Estructura del Proyecto](#-arquitectura-del-proyecto) • [Instalación y Compilación](#-compilación-y-ejecución) • [Controles](#-controles) • [Niveles](#-niveles)

</div>

---

## 🎮 Sobre el Proyecto

**Marble Runner 3D** pone a prueba la precisión, el control de inercia y los reflejos del jugador en pistas suspendidas en el vacío. Controlas una esfera física que debe atravesar circuitos repletos de curvas sin barandillas, desniveles de aceleración brutal, plataformas móviles y obstáculos oscilantes mientras recolectas monedas y buscas el portal de meta antes de caer al abismo.

El motor del juego fue desarrollado desde cero con una arquitectura modular orientada a objetos en C++, implementando simulación física analítica para el rodamiento 3D, resolución de colisiones y una cámara dinámica en tercera persona.

---

## ✨ Características

- ⚙️ **Física de Rodamiento 3D Real:** La esfera calcula en tiempo real su eje de giro perpendicular al vector de velocidad horizontal ($\vec{\omega} = [v_z, 0, -v_x]$) e integra su rotación en matrices de orientación 3D (`MatrixMultiply`), simulando rodamiento y fricción tangencial exacta.
- 📐 **Detección y Respuesta de Colisiones (AABB & Esferas):**
  - Colisión continua esfera-caja contra plataformas sólidas con vectores de penetración y cálculo de rebote elástico.
  - Colisión esfera-esfera de precisión para la recolección fluida de coleccionables.
- 🎥 **Cámara Cinemática en 3ra Persona:** Seguimiento suave mediante interpolación exponencial (*Lerp*) que absorbe impactos y acompaña la inercia del jugador sin vibraciones molestas.
- 🚧 **Pistas Dinámicas & Peligros Móviles:** Plataformas con vaivén senoidal que sirven de puente sobre abismos o como bloques empujadores de barrido.
- 🖥️ **HUD Interactivo:** Marcador de puntaje global, cronómetro por nivel, avisos de reaparición y botones interactivos compatibles con ratón y teclado.

---

## 🕹️ Controles

| Entrada | Acción |
| :--- | :--- |
| <kbd>W</kbd> <kbd>A</kbd> <kbd>S</kbd> <kbd>D</kbd> / <kbd>↑</kbd> <kbd>←</kbd> <kbd>↓</kbd> <kbd>→</kbd> | Mover y rodar la canica |
| <kbd>ESPACIO</kbd> | Salto / Impulso vertical (cuando está apoyada en una plataforma) |
| <kbd>R</kbd> | Reiniciar el nivel actual tras un error o caída |
| <kbd>1</kbd> o **Clic en Botón de Pantalla** | Reiniciar partida completa desde el **Nivel 1** |
| <kbd>ENTER</kbd> | Continuar al siguiente nivel al alcanzar la meta / Reiniciar al ganar |

---

## 🏁 Niveles

El juego cuenta con 3 circuitos de dificultad progresiva diseñados con filosofía arcade:

```
[ Nivel 1: Pradera de Equilibrio ] ──▶ [ Nivel 2: El Desfiladero Veloz ] ──▶ [ Nivel 3: La Espiral del Vértigo ]
      (Curvas y Tablón de 1.5m)               (Pendiente y Plataforma Móvil)               (Islas, Barridos y Salto Final)
```

1. **Nivel 1: "Pradera de Equilibrio"**
   - Introducción a la inercia y fricción.
   - Curvas abiertas que desembocan en el estrecho *Narrow Plank* (tablón de solo 1.5 metros de ancho sin barandillas).
2. **Nivel 2: "El Desfiladero Veloz"**
   - Pendiente escalonada de alta aceleración por gravedad.
   - Curva ciega de 90° con frenado obligado al final del descenso.
   - Cruce sobre el vacío coordinando el salto hacia una **plataforma móvil oscilante**.
3. **Nivel 3: "La Espiral del Vértigo" (Hardcore)**
   - Islas flotantes mínimas sin margen de error.
   - **Bloques empujadores** que barren el camino para expulsar la canica al abismo.
   - Viga de balance hiperestrecha de 1.3 metros.
   - Salto de fe final hacia la plataforma dorada de meta.

---

## 📁 Arquitectura del Proyecto

El código fuente sigue una estructura limpia, desacoplada y orientada a la mantenibilidad:

```
MarbleRunner3D/
├── include/
│   ├── core/
│   │   ├── GameObject.h     # Clase base abstracta (interfaz Update / Draw)
│   │   └── GameManager.h    # Ciclo de vida, HUD, puntuación y transiciones
│   ├── entities/
│   │   ├── Marble.h         # Entidad del jugador, cinemática y matriz de giro
│   │   ├── Platform.h       # Bloques estáticos y plataformas móviles oscilantes
│   │   ├── Coin.h           # Monedas coleccionables con levitación y rotación
│   │   └── Goal.h           # Baliza luminosa de llegada
│   └── levels/
│       ├── Level.h          # Clase base polimórfica para gestión de escenarios
│       ├── Level1.h         # Pradera de Equilibrio
│       ├── Level2.h         # El Desfiladero Veloz
│       └── Level3.h         # La Espiral del Vértigo
├── src/
│   ├── core/
│   │   └── GameManager.cpp
│   ├── entities/
│   │   ├── Marble.cpp
│   │   ├── Platform.cpp
│   │   ├── Coin.cpp
│   │   └── Goal.cpp
│   ├── levels/
│   │   ├── Level.cpp
│   │   ├── Level1.cpp
│   │   ├── Level2.cpp
│   │   └── Level3.cpp
│   └── main.cpp             # Entrada del programa, ventana Raylib y bucle de juego
├── Makefile                 # Automatización de build multiplataforma
├── build.sh                 # Script bash para Linux y WSL
├── build.bat                # Script para Windows / MinGW
└── README.md
```

---

## 🛠️ Compilación y Ejecución

### Requisitos Previos

- Compilador con soporte para **C++17** (`g++`, `clang++` o `MinGW-w64`).
- Biblioteca **[Raylib](https://www.raylib.com/)** (v4.5 o superior).

---

### 🐧 Linux / WSL (Ubuntu, Debian, Fedora, Arch)

1. **Instalar dependencias de desarrollo:**
   ```bash
   # Ubuntu / Debian
   sudo apt update
   sudo apt install -y build-essential libgl-dev libx11-dev
   ```

2. **Compilar usando el script incluido o Make:**
   ```bash
   ./build.sh
   # o alternativamente:
   make
   ```

3. **Ejecutar el juego:**
   ```bash
   ./marble_runner
   ```

---

### 🪟 Windows (MinGW-w64 / w64devkit)

1. Asegúrate de tener `g++` y `raylib` configurados en tu `PATH`.
2. Ejecuta directamente el script por lotes:
   ```cmd
   build.bat
   ```
   *Nota: `build.bat` incluye soporte automático con `pushd` para compilar sin problemas incluso si abres el proyecto desde rutas de red o WSL (`\\wsl.localhost`).*

3. **O compilar manualmente desde la consola:**
   ```cmd
   g++ -std=c++17 -Wall -Wextra -O2 -Iinclude src/main.cpp src/core/*.cpp src/entities/*.cpp src/levels/*.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -o marble_runner.exe
   marble_runner.exe
   ```

---

### 🍏 macOS

1. Instalar Raylib vía Homebrew:
   ```bash
   brew install raylib
   ```
2. Compilar con Make:
   ```bash
   make
   ./marble_runner
   ```

---

## 📦 Tecnologías Utilizadas

- **Lenguaje:** C++17
- **Librería Gráfica y Ventana:** Raylib (OpenGL core profile)
- **Matemáticas y Cinemática:** `raymath` y matrices de transformación 3D locales (`rlgl`)
- **Sistema de Construcción:** GNU Make & Shell Scripts

---

## 📄 Licencia

Este proyecto está bajo la Licencia **MIT** — siéntete libre de clonarlo, bifurcarlo, modificarlo y usarlo en tus propios desarrollos.

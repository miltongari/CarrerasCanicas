#include "levels/Level2.h"

Level2::Level2()
    : Level("Nivel 2: El Desfiladero Veloz", (Vector3){ 0.0f, 6.0f, 2.0f }, -12.0f) {}

void Level2::Build() {
    // 1. Plataforma de salida elevada (Y = +4)
    platforms.push_back(new Platform((Vector3){ 0.0f, 4.0f, 0.0f }, (Vector3){ 6.0f, 1.0f, 6.0f }, ORANGE));

    // 2. Pendiente descendente en gradas (Aceleración masiva tipo Monkey Ball)
    platforms.push_back(new Platform((Vector3){ 0.0f, 2.5f, -7.0f },  (Vector3){ 4.0f, 1.0f, 8.0f }, GOLD));
    platforms.push_back(new Platform((Vector3){ 0.0f, 0.8f, -15.0f }, (Vector3){ 3.2f, 1.0f, 8.0f }, ORANGE));
    platforms.push_back(new Platform((Vector3){ 0.0f, -0.8f, -23.0f }, (Vector3){ 2.8f, 1.0f, 8.0f }, GOLD));

    coins.push_back(new Coin((Vector3){ 0.0f, 3.5f, -6.0f }, 0.35f, 20));
    coins.push_back(new Coin((Vector3){ 0.0f, 1.8f, -14.0f }, 0.35f, 25));
    coins.push_back(new Coin((Vector3){ 0.0f, 0.2f, -22.0f }, 0.35f, 30));

    // 3. Zona de frenado y giro de 90 grados a la derecha (¡Si vas muy rápido caes al vacío!)
    platforms.push_back(new Platform((Vector3){ 4.5f, -1.5f, -29.0f }, (Vector3){ 12.0f, 1.0f, 5.0f }, RED));
    // Valla protectora parcial al fondo
    platforms.push_back(new Platform((Vector3){ 4.5f, -0.7f, -31.6f }, (Vector3){ 12.0f, 0.8f, 0.3f }, MAROON));

    coins.push_back(new Coin((Vector3){ 5.0f, -0.5f, -29.0f }, 0.35f, 30));

    // 4. EL ABISMO: Plataforma móvil que se traslada en el eje X para cruzar el vacío
    // Platform(pos, size, color, moveDir, moveDist, speed)
    platforms.push_back(new Platform((Vector3){ 13.0f, -1.8f, -39.0f }, (Vector3){ 3.5f, 0.8f, 5.0f }, PURPLE,
                                     (Vector3){ 1.0f, 0.0f, 0.0f }, 3.5f, 2.2f));

    coins.push_back(new Coin((Vector3){ 13.0f, -0.8f, -39.0f }, 0.35f, 50));

    // 5. Tramo final y meta
    platforms.push_back(new Platform((Vector3){ 13.0f, -2.2f, -50.0f }, (Vector3){ 6.0f, 1.0f, 10.0f }, ORANGE));
    platforms.push_back(new Platform((Vector3){ 9.9f, -1.4f, -50.0f },  (Vector3){ 0.3f, 0.8f, 10.0f }, MAROON));
    platforms.push_back(new Platform((Vector3){ 16.1f, -1.4f, -50.0f }, (Vector3){ 0.3f, 0.8f, 10.0f }, MAROON));

    goal = new Goal((Vector3){ 13.0f, -1.6f, -52.0f }, 1.8f);
}

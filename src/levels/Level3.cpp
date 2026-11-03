#include "levels/Level3.h"

Level3::Level3()
    : Level("Nivel 3: La Espiral del Vértigo", (Vector3){ 0.0f, 2.0f, 0.0f }, -14.0f) {}

void Level3::Build() {
    // 1. Plataforma de salida compacta (Azul profundo y magenta neón)
    platforms.push_back(new Platform((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 4.5f, 1.0f, 4.5f }, DARKBLUE));
    coins.push_back(new Coin((Vector3){ 0.0f, 1.0f, -1.0f }, 0.35f, 25));

    // 2. Primera isla diminuta con salto o impulso
    platforms.push_back(new Platform((Vector3){ 0.0f, 0.5f, -7.0f }, (Vector3){ 2.5f, 1.0f, 3.5f }, VIOLET));
    coins.push_back(new Coin((Vector3){ 0.0f, 1.5f, -7.0f }, 0.35f, 30));

    // 3. Giro hacia la derecha: bloque estrecho
    platforms.push_back(new Platform((Vector3){ 5.0f, 1.0f, -7.0f }, (Vector3){ 5.0f, 1.0f, 2.2f }, MAGENTA));

    // 4. PRIMER OBSTÁCULO MÓVIL: Bloque empujador que barre de adelante hacia atrás
    platforms.push_back(new Platform((Vector3){ 9.0f, 1.5f, -7.0f }, (Vector3){ 2.2f, 1.2f, 2.2f }, RED,
                                     (Vector3){ 0.0f, 0.0f, 1.0f }, 2.4f, 3.0f));

    // 5. Isla intermedia
    platforms.push_back(new Platform((Vector3){ 13.0f, 1.8f, -7.0f }, (Vector3){ 3.5f, 1.0f, 3.5f }, DARKBLUE));
    coins.push_back(new Coin((Vector3){ 13.0f, 2.8f, -7.0f }, 0.35f, 50));

    // 6. Curva hacia adelante con rampa ascendente
    platforms.push_back(new Platform((Vector3){ 13.0f, 2.5f, -15.0f }, (Vector3){ 2.0f, 1.0f, 8.0f }, VIOLET));
    coins.push_back(new Coin((Vector3){ 13.0f, 3.5f, -15.0f }, 0.35f, 40));

    // 7. SEGUNDO OBSTÁCULO MÓVIL: Plataforma oscilante sobre el abismo más profundo
    platforms.push_back(new Platform((Vector3){ 13.0f, 3.0f, -23.0f }, (Vector3){ 3.0f, 0.8f, 3.5f }, MAGENTA,
                                     (Vector3){ 1.0f, 0.0f, 0.0f }, 3.5f, 2.8f));

    // 8. Tramo de balance hiperestrecho (¡Solo 1.3m de ancho!)
    platforms.push_back(new Platform((Vector3){ 7.0f, 3.6f, -30.0f }, (Vector3){ 10.0f, 1.0f, 1.3f }, RED));
    coins.push_back(new Coin((Vector3){ 7.0f, 4.6f, -30.0f }, 0.35f, 50));

    // 9. Salto final hacia la isla de meta (Gap en el aire: requiere velocidad para cruzar)
    platforms.push_back(new Platform((Vector3){ 0.0f, 3.8f, -38.0f }, (Vector3){ 5.0f, 1.0f, 5.0f }, GOLD));
    platforms.push_back(new Platform((Vector3){ 0.0f, 4.4f, -40.6f }, (Vector3){ 5.0f, 0.6f, 0.2f }, YELLOW));

    goal = new Goal((Vector3){ 0.0f, 4.2f, -38.0f }, 1.8f);
}

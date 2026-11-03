#include "levels/Level1.h"

Level1::Level1()
    : Level("Nivel 1: Pradera de Equilibrio", (Vector3){ 0.0f, 2.0f, 2.0f }, -8.0f) {}

void Level1::Build() {
    // 1. Plataforma de salida con barandillas
    platforms.push_back(new Platform((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 6.0f, 1.0f, 8.0f }, LIME));
    platforms.push_back(new Platform((Vector3){ -3.1f, 0.7f, 0.0f }, (Vector3){ 0.3f, 0.7f, 8.0f }, DARKGREEN));
    platforms.push_back(new Platform((Vector3){  3.1f, 0.7f, 0.0f }, (Vector3){ 0.3f, 0.7f, 8.0f }, DARKGREEN));

    coins.push_back(new Coin((Vector3){ 0.0f, 1.0f, -2.0f }, 0.35f, 10));

    // 2. Primera curva hacia la izquierda (sin vallas)
    platforms.push_back(new Platform((Vector3){ -2.5f, -0.2f, -8.0f }, (Vector3){ 4.5f, 1.0f, 8.0f }, GREEN));
    coins.push_back(new Coin((Vector3){ -2.5f, 0.8f, -8.0f }, 0.35f, 15));

    // 3. Conexión hacia la derecha
    platforms.push_back(new Platform((Vector3){ 2.0f, -0.5f, -17.0f }, (Vector3){ 5.0f, 1.0f, 10.0f }, LIME));
    coins.push_back(new Coin((Vector3){ 2.0f, 0.5f, -15.0f }, 0.35f, 20));
    coins.push_back(new Coin((Vector3){ 2.0f, 0.5f, -19.0f }, 0.35f, 20));

    // 4. EL TABLÓN DEL EQUILIBRIO (Estrecho: solo 1.5 metros de ancho, ¡típico de Monkey Ball!)
    platforms.push_back(new Platform((Vector3){ 2.0f, -0.8f, -31.0f }, (Vector3){ 1.5f, 1.0f, 18.0f }, DARKGREEN));
    coins.push_back(new Coin((Vector3){ 2.0f, 0.2f, -27.0f }, 0.35f, 25));
    coins.push_back(new Coin((Vector3){ 2.0f, 0.2f, -34.0f }, 0.35f, 25));

    // 5. Plataforma de meta
    platforms.push_back(new Platform((Vector3){ 2.0f, -1.1f, -44.0f }, (Vector3){ 8.0f, 1.0f, 8.0f }, LIME));
    platforms.push_back(new Platform((Vector3){ 2.0f, -0.3f, -48.1f }, (Vector3){ 8.0f, 0.8f, 0.3f }, DARKGREEN));

    goal = new Goal((Vector3){ 2.0f, -0.5f, -44.0f }, 1.8f);
}

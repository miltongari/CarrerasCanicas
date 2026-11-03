#include "entities/Marble.h"
#include "rlgl.h"
#include <cmath>

Marble::Marble(Vector3 startPos, float r, Color col)
    : GameObject(startPos, col),
      velocity({ 0.0f, 0.0f, 0.0f }),
      startPosition(startPos),
      radius(r),
      acceleration(28.0f),
      maxSpeed(18.0f),       // Mayor velocidad tope para sensación vertiginosa tipo Monkey Ball
      friction(2.4f),        // Fricción moderada para mantener inercia
      gravity(-24.0f),
      isGrounded(false),
      rotationMatrix(MatrixIdentity()) {}

void Marble::Update(float dt) {
    // 1. CAPTURA DE ENTRADA
    Vector3 inputDir = { 0.0f, 0.0f, 0.0f };
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    inputDir.z -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  inputDir.z += 1.0f;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  inputDir.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) inputDir.x += 1.0f;

    float inputLen = sqrtf(inputDir.x * inputDir.x + inputDir.z * inputDir.z);
    if (inputLen > 0.001f) {
        inputDir.x /= inputLen;
        inputDir.z /= inputLen;
    }

    // 2. ACELERACIÓN
    velocity.x += inputDir.x * acceleration * dt;
    velocity.z += inputDir.z * acceleration * dt;

    // 3. FRICCIÓN / INERCIA
    float currentFriction = isGrounded ? friction : (friction * 0.35f);
    velocity.x -= velocity.x * currentFriction * dt;
    velocity.z -= velocity.z * currentFriction * dt;

    // 4. LÍMITE DE VELOCIDAD HORIZONTAL
    float horizSpeed = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (horizSpeed > maxSpeed) {
        velocity.x = (velocity.x / horizSpeed) * maxSpeed;
        velocity.z = (velocity.z / horizSpeed) * maxSpeed;
    }

    // 5. SALTO
    if (isGrounded && IsKeyPressed(KEY_SPACE)) {
        velocity.y = 8.8f;
        isGrounded = false;
    }

    // 6. GRAVEDAD
    velocity.y += gravity * dt;

    // 7. INTEGRACIÓN DE POSICIÓN
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;

    // 8. FÍSICA CINEMÁTICA DE RODAMIENTO 3D
    // El eje de rotación es perpendicular al vector de velocidad horizontal en el plano del suelo:
    // Eje = (vz, 0, -vx) normalizado para que ruede hacia adelante y no invertido.
    if (horizSpeed > 0.02f) {
        Vector3 rotationAxis = { velocity.z / horizSpeed, 0.0f, -velocity.x / horizSpeed };
        float angularSpeed = (horizSpeed / radius) * dt; // dTheta = (v / r) * dt en radianes

        // Creamos la rotación incremental y la multiplicamos por la orientación acumulada
        Matrix deltaRotation = MatrixRotate(rotationAxis, angularSpeed);
        rotationMatrix = MatrixMultiply(deltaRotation, rotationMatrix);
    }

    isGrounded = false;
}

void Marble::Draw() {
    if (!active) return;

    // Aplicamos la matriz de transformación local para que la esfera ruede visualmente en el espacio
    rlPushMatrix();
        rlTranslatef(position.x, position.y, position.z);
        rlMultMatrixf(MatrixToFloat(rotationMatrix));

        // 1. Esfera base común y corriente (color uniforme)
        DrawSphere((Vector3){ 0.0f, 0.0f, 0.0f }, radius, color);

        // 2. Malla sutil que permite ver la rotación de la esfera en 3D
        DrawSphereWires((Vector3){ 0.0f, 0.0f, 0.0f }, radius + 0.001f, 10, 10, ColorAlpha(BLACK, 0.25f));

        // 3. Pequeño punto sutil de referencia visual que gira con la esfera
        DrawSphere((Vector3){ 0.0f, radius * 0.70f, radius * 0.50f }, radius * 0.12f, ColorAlpha(WHITE, 0.40f));

    rlPopMatrix();
}

void Marble::ResolveBoxCollision(const BoundingBox& box) {
    if (!CheckCollisionBoxSphere(box, position, radius)) return;

    float closestX = fmaxf(box.min.x, fminf(position.x, box.max.x));
    float closestY = fmaxf(box.min.y, fminf(position.y, box.max.y));
    float closestZ = fmaxf(box.min.z, fminf(position.z, box.max.z));

    float diffX = position.x - closestX;
    float diffY = position.y - closestY;
    float diffZ = position.z - closestZ;
    float distSq = diffX * diffX + diffY * diffY + diffZ * diffZ;

    if (distSq < radius * radius) {
        float dist = sqrtf(distSq);

        if (dist < 0.0001f) {
            position.y = box.max.y + radius;
            velocity.y = 0.0f;
            isGrounded = true;
            return;
        }

        float normalX = diffX / dist;
        float normalY = diffY / dist;
        float normalZ = diffZ / dist;
        float penetration = radius - dist;

        position.x += normalX * penetration;
        position.y += normalY * penetration;
        position.z += normalZ * penetration;

        if (normalY > 0.6f) {
            if (velocity.y < 0.0f) velocity.y = 0.0f;
            isGrounded = true;
        } else {
            float dotVel = velocity.x * normalX + velocity.y * normalY + velocity.z * normalZ;
            if (dotVel < 0.0f) {
                velocity.x -= 1.4f * dotVel * normalX;
                velocity.z -= 1.4f * dotVel * normalZ;
            }
        }
    }
}

void Marble::Reset() {
    position = startPosition;
    velocity = (Vector3){ 0.0f, 0.0f, 0.0f };
    isGrounded = false;
    rotationMatrix = MatrixIdentity();
}

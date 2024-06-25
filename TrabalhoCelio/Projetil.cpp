#include "Projetil.h" // Include your header file
#include <math.h>

Projetil::Projetil(float x, float y, float speed, float angle, ALLEGRO_BITMAP* image)
    : x(x), y(y), speed(speed), angle(angle), image(image) {}

void Projetil::update(float deltaTime) {
    x += speed * cos(angle) * deltaTime; // Adjust for angled movement if needed
    y += speed * sin(angle) * deltaTime;
}

bool Projetil::isOutOfBounds(int screenWidth, int screenHeight) {
    return (x < 0 || x > screenWidth || y < 0 || y > screenHeight);
}
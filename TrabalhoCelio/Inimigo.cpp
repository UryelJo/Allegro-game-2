#include "Inimigo.h"
#include <math.h>

Inimigo::Inimigo(float x, float y, float speed, float angle, ALLEGRO_BITMAP* image)
	: x(x), y(y), speed(speed), angle(angle), image(image) {}

void Inimigo::update(float deltaTime) {

}

bool Inimigo::isOutOfBounds(int screenWidth, int screenHeight) {
	return (x < 0 || x > screenWidth || y < 0 || y > screenHeight);
}


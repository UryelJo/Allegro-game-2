#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <math.h>

class Inimigo
{
public:
	Inimigo(float x, float y, float speed, float angle, ALLEGRO_BITMAP* image);
	void update(float deltaTime);
	bool isOutOfBounds(int screenWidth, int screenHeight);
	ALLEGRO_BITMAP* image;
	float x, y;
	float speed;
	float angle;
	float x_velocity;
	float y_velocity;

	void moverPara(float alvoX, float alvoY) {
		// Calcula a direção para o personagem principal
		float dx = alvoX - x;
		float dy = alvoY - y;
		float distancia = sqrt(dx * dx + dy * dy);

		// Move o inimigo em direção ao personagem principal
		if (distancia > 0) {
			x += (dx / distancia) * x_velocity;
			y += (dy / distancia) * y_velocity;
		}
	}
};


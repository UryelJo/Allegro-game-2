#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Projetil {
public:
    // Constructor (optional): Initialize projectile properties
    Projetil(float x, float y, float speed, float angle, ALLEGRO_BITMAP* image);

    // Update position based on speed and elapsed time
    void update(float deltaTime);

    // Check if projectile is out of bounds (optional)
    bool isOutOfBounds(int screenWidth, int screenHeight);
    ALLEGRO_BITMAP* image; // Pointer to the projectile's image (optional)
    float x, y;            // Projectile's position
    float speed;           // Projectile's speed
    float angle;           // Projectile's direction (optional for angled movement)
    float x_velocity;
    float y_velocity;
};
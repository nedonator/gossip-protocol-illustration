#include "Project.h"

extern const double MAX_SPEED;
extern const double ACC_TIME;
extern const int FPS;
extern const int HEIGHT;
extern const int WIDTH;
extern const int PLAYER_SIZE;
extern std::set<Unit*> units;
Image* bullet;
Image* enemy;

Unit::Unit(Image** image, Graphics* graphics, double x, double y) {
	this->x = x;
	this->y = y;
	this->image = image;
	this->graphics = graphics;
	imageNumber = 0;
}

void Unit::draw() {
	if (image)
		graphics->DrawImage(image[imageNumber], (int)x-PLAYER_SIZE/2, (int)y-PLAYER_SIZE/2);
}














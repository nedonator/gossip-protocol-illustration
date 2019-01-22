#include "Signal.h"

extern const int FPS;

Signal::Signal(Image* image, Graphics* graphics, double x, double y, double destX, double destY, double speed) {
	this->image = image;
	this->graphics = graphics;
	this->x = x;
	this->y = y;
	this->destX = destX;
	this->destY = destY;
	double norm = sqrt(pow(destX - x, 2) + pow(destY - y, 2));
	this->vx = speed * (destX - x) / norm;
	this->vy = speed * (destY - y) / norm;
}

void Signal::update() {
	x += vx / FPS;
	y += vy / FPS;
}

bool Signal::isAlive() {
	double sc = vx * (destX - x) + vy * (destY - y);
	return sc > 0;
}

void Signal::draw() {
	graphics->DrawImage(image, (int)x - 2, (int)y - 2);
}
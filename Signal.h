#pragma once
#include "Project.h"
class Signal {
public:
	double x;
	double y;
	double vx;
	double vy;
	double destX;
	double destY;
	Image* image;
	Graphics* graphics;
	Signal(Image* image, Graphics* graphics, double x, double y, double destX, double destY, double speed);
	bool isAlive();
	void update();
	void draw();
};
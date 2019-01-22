#ifndef _UNITS_H
#define _UNITS_H
#include "Image.h"
#include "Graphics.h"
#include "Project.h"

class Unit{
protected:
	//0 - player, 1 - doll, 2 - enemy, 3 - wall, 4 - corner, 5 - bullet
	int type;
	Image** image;
	Graphics* graphics;
public:
	Unit(Image** image, Graphics* graphics, double x, double y);
	int imageNumber;
	double x;
	double y;
	void draw();
};

#endif
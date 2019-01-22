#pragma once
#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "Project.h"

#include "Image.h"
class Image;

class Graphics
{
private:
	SDL_Surface* Screen;
	void* Window;
	void* Renderer;
	void* Texture;

public:
	Graphics(int width, int height);

	Image* NewImage(char* file);
	Image* NewImage(char* file, int r, int g, int b);
	bool DrawImage(Image* img, int x, int y);
	void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b);

	void Flip();
};

#endif
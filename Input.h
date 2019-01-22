#ifndef _INPUT_H_
#define _INPUT_H_

#include "Project.h"

class Input
{
private:
	SDL_Event evt;
	bool isMouseDown = false;
	int x;
	int y;
	bool exit = false;

public:
	void Update();

	bool IsMouseButtonDown();
	bool IsMouseButtonUp();
	POINT GetButtonDownCoords();

	/*bool IsKeyDown(byte key);
	bool IsKeyUp(byte key);
	byte GetPressedKey();*/

	bool IsExit();
};

#endif
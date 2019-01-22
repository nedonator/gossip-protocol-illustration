#include "Input.h"

void Input::Update()
{
	while (SDL_PollEvent(&evt)) {
		if (evt.type == SDL_MOUSEBUTTONDOWN) {
			isMouseDown = true;
			x = evt.button.x;
			y = evt.button.y;
		}
		else if (evt.type == SDL_MOUSEBUTTONUP)
			isMouseDown = false;
		//else if (evt.type == SDL_QUIT)
			//exit = true;
	}
}

bool Input::IsMouseButtonDown()
{
	return isMouseDown;
}

bool Input::IsMouseButtonUp()
{
	return !isMouseDown;
}

POINT Input::GetButtonDownCoords()
{
	POINT point;
	point.x = x;
	point.y = y;

	return point;
}

/*bool Input::IsKeyDown(byte key)
{
	return (evt.type == SDL_KEYDOWN && evt.key.keysym.sym == key);
}

bool Input::IsKeyUp(byte key)
{
	return (evt.type == SDL_KEYUP && evt.key.keysym.sym == key);
}

byte Input::GetPressedKey()
{
	return evt.key.keysym.sym;
}*/

bool Input::IsExit()
{
	//return (evt.type == SDL_QUIT);
	//return exit;
	return false;
}
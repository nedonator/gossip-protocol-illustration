#include "Graphics.h"

Graphics::Graphics(int width, int height)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(width, height, 0, (SDL_Window**)&Window, (SDL_Renderer**)&Renderer);
	Screen = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	Texture = SDL_CreateTexture((SDL_Renderer*)Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	SDL_SetRenderDrawColor((SDL_Renderer*)Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

Image* Graphics::NewImage(char* file)
{
	Image* image = new Image();
	image->surf = SDL_LoadBMP(file);
	return image;
}

Image* Graphics::NewImage(char* file, int r, int g, int b)
{
	Image* image = new Image();
	image->surf = SDL_LoadBMP(file);
	SDL_SetColorKey(image->surf, SDL_TRUE, SDL_MapRGB(image->surf->format, 255, 255, 255));
	return image;
}

bool Graphics::DrawImage(Image* img, int x, int y)
{
	if (Screen == NULL || img->surf == NULL)
		return false;

	SDL_Rect Area;
	Area.x = x;
	Area.y = y;

	SDL_BlitSurface(img->surf, NULL, Screen, &Area);

	return true;
}

void Graphics::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b) {
	SDL_SetRenderDrawColor((SDL_Renderer*)Renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine((SDL_Renderer*)Renderer,x1,y1,x2,y2);
}

void Graphics::Flip()
{
	SDL_SetColorKey(Screen, SDL_TRUE, SDL_MapRGB(Screen->format, 0, 0, 0));
	SDL_UpdateTexture((SDL_Texture*)Texture, NULL, Screen->pixels, Screen->pitch);
	SDL_SetTextureBlendMode((SDL_Texture*)Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy((SDL_Renderer*)Renderer, (SDL_Texture*)Texture, NULL, NULL);
	SDL_RenderPresent((SDL_Renderer*)Renderer);
	SDL_RenderClear((SDL_Renderer*)Renderer);
	SDL_FillRect(Screen, NULL, 0x000000);
	SDL_SetRenderDrawColor((SDL_Renderer*)Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect((SDL_Renderer*)   Renderer, NULL);
}
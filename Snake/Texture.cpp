#include "Texture.h"


Texture::Texture() : gTexture(nullptr), width(0), height(0)
{
}


Texture::~Texture()
{
	free();
}

bool Texture::loadImage(std::string path, SDL_Renderer *renderer)
{
	free();
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (!loadedSurface)
		printf("Unable to load image on path: %s! SDL_image_error: %s.\n",
		path.c_str(), IMG_GetError());
	else
	{
		if (SDL_SetColorKey(loadedSurface, 1, SDL_MapRGB(loadedSurface->format,
			255, 255, 255)) == -1)
			printf("Failed to set color key!\n");

		gTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (!gTexture)
			printf("Failed to create texture from surface! SDL_Error: %s.\n",
			SDL_GetError());
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	
	return gTexture != nullptr;
}

void Texture::free()
{
	if (gTexture)
		SDL_DestroyTexture(gTexture);
	width = height = 0;
}

void Texture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect *clipRect,
	double angle, SDL_Point *center)
{
	SDL_Rect destRect = { x, y, width, height };

	if (clipRect)
	{
		destRect.h = clipRect->h;
		destRect.w = clipRect->w;
	}
	
	SDL_RenderCopyEx(renderer, gTexture, clipRect, &destRect, angle, center, 
		SDL_FLIP_NONE);
}
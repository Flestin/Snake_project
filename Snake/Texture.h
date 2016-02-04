#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
private:
	SDL_Texture *gTexture;
	int width, height;

public:
	Texture();
	~Texture();

	bool loadImage(std::string path, SDL_Renderer *renderer);
	void free();
	void render(int x, int y, SDL_Renderer *renderer, SDL_Rect *clipRect = nullptr,
		double angle = 0.0, SDL_Point *center = nullptr);

	int getWidth();
	int getHeight();
};


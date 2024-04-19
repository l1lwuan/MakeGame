#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Background {
public:
	Background(SDL_Renderer* renderer, const char* imagePath);
	~Background();
	void render(SDL_Rect rect);
private:
	SDL_Texture* image;
	SDL_Renderer* renderer;
};

#endif // BACKGROUND_HPP
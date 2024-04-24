#ifndef SKILLS_HPP
#define SKILLS_HPP
#include "SDL.h"
#include "SDL_image.h"

class Skills {
public:
	Skills(SDL_Renderer* renderer, const char* imagePath, int posX, int posY, int frameWidth, int frameHeight, int numFrames, int currentFrame);
	~Skills();
	void render();
	void updateAnimation();
	void touched();
private:
	SDL_Rect destRect;
	SDL_Renderer* renderer;
	SDL_Texture* image;
	int numFrames;
	int frameWidth;
	int frameHeight;
	int currentFrame;
	int posX;
	int posY;

};
#endif // !SKILLS_HPP

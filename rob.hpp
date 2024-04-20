#ifndef ROB_HPP
#define ROB_HPP
#include "SDL.h"
#include "SDL_image.h"

class Rob {
public:
	Rob(SDL_Renderer* renderer, const char* imagePath, int x, int y, int radius);
	~Rob();
	void render();
	void update();
	void handleEvent(SDL_Event& e);
private:
	SDL_Rect destRect;
	SDL_Renderer* renderer;
	SDL_Texture* image;
	int centerX;
	int centerY;
	int radius;
	double angle;
	bool round;
	bool isMoving = true;
};
#endif // !ROB_HPP

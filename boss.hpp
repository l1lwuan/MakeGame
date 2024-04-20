#ifndef BOSS_HPP
#define BOSS_HPP
#include "SDL.h"
#include "SDL_image.h"

class Boss {
public:
	Boss(SDL_Renderer render, const char* imagePath, float x, float y, int frameWidth, int frameHeight, int numFrames, int health, float speed);
	~Boss();
	void render();
	void move();
	void updateAnimation();
	void event(int time);
private:
	float x;
	float y;
	int frameWidth;
	int frameHeight;
	int numFrames;
	float speed;
	bool isTouched;
	bool isTime;
};
#endif // !BOSS_HPP

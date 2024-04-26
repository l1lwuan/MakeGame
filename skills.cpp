#include "skills.hpp"

Skills::Skills(SDL_Renderer* renderer, const char* imagePath, int posX, int posY, int frameWidth, int frameHeight, int numFrames, int currentFrame)
	:renderer(renderer), posX(posX), posY(posY), frameWidth(frameWidth), frameHeight(frameHeight), numFrames(numFrames), currentFrame(0) {

	SDL_Surface* surface = IMG_Load(imagePath);
	image = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	destRect.w = frameWidth;
	destRect.h = frameHeight;
	destRect.x = posX;
	destRect.y = posY;
}

Skills::~Skills() {
	SDL_DestroyTexture(image);
}

void Skills::render() {
	SDL_Rect srcRect = { int(currentFrame / 15) * frameWidth, 0, frameWidth, frameHeight };
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(renderer, image, &srcRect, &destRect, 0.0, nullptr, flip);
}

void Skills::updateAnimation() {
	currentFrame = (currentFrame + 1) % (numFrames * 20);
}


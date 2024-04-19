#include "character.hpp"
#include <iostream>

SDL_Surface* remove(SDL_Surface* surface) {
    if (surface == nullptr) {
        std::cerr << "Invalid surface" << std::endl;
        return nullptr;
    }

    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);

    SDL_SetColorKey(surface, SDL_TRUE, white);

    return surface;
}

Character::Character(SDL_Renderer* renderer, const char* imagePath, int x, int y, int minX, int maxX, int minY, int maxY, int frameWidth, int frameHeight, int numFrames, int speed)
    : renderer(renderer), minX(minX), maxX(maxX), minY(minY), maxY(maxY), posX(x), posY(y), frameWidth(frameWidth), frameHeight(frameHeight), numFrames(numFrames), speed(speed), movingLeft(false), currentFrame(0) {
    SDL_Surface* surface = IMG_Load(imagePath);
    surface = remove(surface);
    spriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    destRect.w = frameWidth;
    destRect.h = frameHeight;
    destRect.x = posX;
    destRect.y = posY;
}

Character::~Character() {
    SDL_DestroyTexture(spriteSheet);
}

void Character::render() {
    SDL_Rect srcRect = { int(currentFrame / 15) * frameWidth, 0, frameWidth, frameHeight };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (movingLeft) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    SDL_RenderCopyEx(renderer, spriteSheet, &srcRect, &destRect, 0.0, nullptr, flip);
}

void Character::move() {
    if (movingLeft) {
        posX -= speed;
        if (posX <= minX) {
            movingLeft = false;
        }
    }
    else {
        posX += speed;
        if (posX >= maxX) {
            movingLeft = true;
        }
    }
    destRect.x = posX;
    destRect.y = posY;
}

void Character::updateAnimation() {

    currentFrame = (currentFrame + 1) % (numFrames * 15);
    std::cout << currentFrame << "\n";
}

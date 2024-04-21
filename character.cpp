#include "character.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int random(int min, int max) {
    static bool initialized = false;
    if (!initialized) {
        srand(time(nullptr));
        initialized = true;
    }
    return min + rand() % (max - min + 1);
}

SDL_Point randomInitialPosition(int screenWidth, int screenHeight, int characterWidth, int characterHeight) {
    int side = random(0, 1);
    int x, y;

    if (side == 0) { 
        x = -characterWidth;
        y = random(380, screenHeight - characterHeight);
    }
    else {
        x = screenWidth;
        y = random(380, screenHeight - characterHeight);
    }

    return SDL_Point{ x, y };
}

Character::Character(SDL_Renderer* renderer, const char* imagePath, int screenWidth, int screenHeight, int frameWidth, int frameHeight, int numFrames, int speed)
    : renderer(renderer), frameWidth(frameWidth), frameHeight(frameHeight), numFrames(numFrames), speed(speed), movingLeft(false), currentFrame(0) {

    SDL_Point initialPosition = randomInitialPosition(screenWidth, screenHeight, frameWidth, frameHeight);
    posX = initialPosition.x;
    posY = initialPosition.y;

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
    SDL_RenderDrawRect(renderer, &destRect);
}

void Character::move(int screenWidth, int screenHeight) {
    if (movingLeft) {
        posX -= speed;
        if (posX <= -frameWidth) { // If character is completely off-screen on the left
            SDL_Point initialPosition = randomInitialPosition(screenWidth, screenHeight, frameWidth, frameHeight);
            posX = initialPosition.x;
            posY = initialPosition.y;
            movingLeft = false;
        }
    }
    else {
        posX += speed;
        if (posX >= screenWidth) { // If character is completely off-screen on the right
            SDL_Point initialPosition = randomInitialPosition(screenWidth, screenHeight, frameWidth, frameHeight);
            posX = initialPosition.x;
            posY = initialPosition.y;
            movingLeft = true;
        }
    }
    destRect.x = posX;
    destRect.y = posY;
}

void Character::updateAnimation() {
    currentFrame = (currentFrame + 1) % (numFrames * 15);
}


SDL_Surface* Character::remove(SDL_Surface* surface) {
    if (surface == nullptr) {
        std::cerr << "Invalid surface" << std::endl;
        return nullptr;
    }

    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);

    SDL_SetColorKey(surface, SDL_TRUE, white);

    return surface;
}


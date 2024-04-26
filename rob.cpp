#include "rob.hpp"
#include "character.hpp"

#include <iostream>
#include "skills.hpp"

Rob::Rob(SDL_Renderer* renderer, const char* imagePath, int x, int y, int radius)
    : renderer(renderer), centerX(x), centerY(y), radius(radius), angle(7 * M_PI / 6), round(true),
    isMoving(true), keepDirection(false) {
    SDL_Surface* surface = IMG_Load(imagePath);
    image = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(image, NULL, NULL, &destRect.w, &destRect.h);
    destRect.x = centerX + static_cast<int>(radius * -cos(angle)) - destRect.w / 2;
    destRect.y = centerY + static_cast<int>(radius * -sin(angle)) - destRect.h / 2;

}

Rob::~Rob() {
    SDL_DestroyTexture(image);
}

void Rob::render() {
    SDL_Point temp = { 0, 0 };
    SDL_RenderCopyEx(renderer, image, NULL, &destRect, angle / M_PI * 180 +90, &temp, SDL_FLIP_NONE);
}

void Rob::update() {
    if (isMoving && !keepDirection) {
        if (round) {
            angle += M_PI / 180;
            if (angle >= 11 * M_PI / 6) {
                round = false;
            }
        } else {
            angle -= M_PI / 180;
            if (angle <= 7 * M_PI / 6) {
                round = true;
            }
        }
        destRect.x = centerX + static_cast<int>(radius * -cos(angle)) - destRect.w / 2;
        destRect.y = centerY + static_cast<int>(radius * -sin(angle)) - destRect.h / 2;

    }
    else if (isMoving && keepDirection) {
        centerX += static_cast<int>(2 * -cos(angle));
        centerY += static_cast<int>(2 * -sin(angle));
        destRect.x = centerX + static_cast<int>(radius * -cos(angle)) - destRect.w / 2 + 5;
        destRect.y = centerY + static_cast<int>(radius * -sin(angle)) - destRect.h / 2 + 5;

    }
    if (destRect.x >= 1260 || destRect.y >= 780 || destRect.x <= 0 ||  isMoving == false) {
        isMoving = true;
        keepDirection = false;
        round = true;
        angle = 3 * M_PI / 2;
        centerX = 650;
        centerY = 330;
        radius = 30;
        destRect.x = centerX + static_cast<int>(radius * -cos(angle)) - destRect.w / 2 + 5;
        destRect.y = centerY + static_cast<int>(radius * -sin(angle)) - destRect.h / 2 + 5;
    }
}

void Rob::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (e.key.keysym.sym == SDLK_SPACE) {
            isMoving = true;
            keepDirection = true;
        }
    }
}

void Rob::touched() {
    isMoving = false;
}

SDL_Rect Rob::getDestRect() {
    return destRect;
}

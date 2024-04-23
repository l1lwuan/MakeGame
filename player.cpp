#include "player.hpp"
#include <iostream>
#include <cmath>

SDL_Surface* remove1(SDL_Surface* surface) {
    if (surface == nullptr) {
        std::cout<< "Invalid surface" << std::endl;
        return nullptr;
    }

    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);

    SDL_SetColorKey(surface, SDL_TRUE, white);

    return surface;
}

Player::Player(SDL_Renderer* renderer, const char* imagePath, int x, int y, int radius)
    : renderer(renderer), centerX(x), centerY(y), radius(radius), angle(7 * M_PI / 6), round(true) {
    SDL_Surface* surface = IMG_Load(imagePath);
    surface = remove1(surface);
    image = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(image, NULL, NULL, &destRect.w, &destRect.h);
    destRect.x = centerX + static_cast<int>(radius * -cos(angle)) - destRect.w / 2;
    destRect.y = centerY + static_cast<int>(radius * -sin(angle)) - destRect.h / 2;
}

Player::~Player() {
    SDL_DestroyTexture(image);
}

void Player::render() {
    SDL_RenderCopyEx(renderer, image, NULL, &destRect, angle / M_PI * 180 + 90, NULL, SDL_FLIP_NONE);
    SDL_RenderDrawRect(renderer, &destRect);
}

void Player::update() {
    if (isMoving) {
        if (round) {
            angle += M_PI / 180;
            if (angle >= 11 * M_PI / 6) {
                round = false;
            }
        }
        else {
            angle -= M_PI / 180;
            if (angle <= 7 * M_PI / 6) {
                round = true;
            }
        }

        destRect.x = centerX + static_cast<int>(radius * -cos(angle)) - destRect.w / 2;
        destRect.y = centerY + static_cast<int>(radius * -sin(angle)) - destRect.h / 2;
    }
    else {
        destRect.x = -10;
        destRect.y = -10;
    }
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE) {
        isMoving = false;
    }
}




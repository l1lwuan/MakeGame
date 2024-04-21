//#include "boss.hpp"
//#include <iostream>
//
//SDL_Surface* remove(SDL_Surface* surface) {
//    if (surface == nullptr) {
//        std::cerr << "Invalid surface" << std::endl;
//        return nullptr;
//    }
//
//    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);
//
//    SDL_SetColorKey(surface, SDL_TRUE, white);
//
//    return surface;
//}
//
//Boss::Boss(SDL_Renderer* renderer, const char* imagePath, float x, float y, int frameWidth, int frameHeight, int numFrames, int health, float speed)
//    : renderer(renderer), x(x), y(y), frameWidth(frameWidth), frameHeight(frameHeight), numFrames(numFrames), health(health), speed(speed), currentFrame(0) {
//    SDL_Surface* surface = IMG_Load(imagePath);
//    surface = remove(surface);
//    spriteSheet = SDL_CreateTextureFromSurface(renderer, surface);
//    SDL_FreeSurface(surface);
//
//    destRect.w = 200;
//    destRect.h = 200;
//    destRect.x = x;
//    destRect.y = y;
//}
//
//Boss::~Boss() {
//    SDL_DestroyTexture(spriteSheet);
//}
//
//void Boss::render() {
//    
//}
//
//void Boss::move() {
//    x -= speed;
//}